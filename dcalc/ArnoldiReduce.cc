

// (c) 2018 Nefelus, Inc.
//
// Author: W. Scott

#include "ArnoldiReduce.hh"

#include "Debug.hh"
#include "MinMax.hh"
#include "Sdc.hh"
#include "Network.hh"
#include "Units.hh"
#include "Arnoldi.hh"
#include "parasitics/ConcreteParasiticsPvt.hh"

namespace sta
{

  rcmodel::rcmodel() : pinV(nullptr)
  {
  }

  rcmodel::~rcmodel()
  {
    free(pinV);
  }

  float
  rcmodel::capacitance() const
  {
    return ctot;
  }



  ////////////////////////////////////////////////////////////////

  const int ArnoldiReduce::ts_point_count_incr_ = 1024;
  const int ArnoldiReduce::ts_edge_count_incr_ = 1024;

  ArnoldiReduce::ArnoldiReduce(StaState *sta) : StaState(sta),
                                                ts_pointNmax(1024),
                                                ts_edgeNmax(1024),
                                                termNmax(256),
                                                dNmax(8)
  {
    ts_pointV = (ts_point *)malloc(ts_pointNmax * sizeof(ts_point));
    ts_ordV = (int *)malloc(ts_pointNmax * sizeof(int));
    ts_pordV = (ts_point **)malloc(ts_pointNmax * sizeof(ts_point *));
    _u0 = (double *)malloc(ts_pointNmax * sizeof(double));
    _u1 = (double *)malloc(ts_pointNmax * sizeof(double));
    y = (double *)malloc(ts_pointNmax * sizeof(double));
    iv = (double *)malloc(ts_pointNmax * sizeof(double));
    r = (double *)malloc(ts_pointNmax * sizeof(double));
    c = (double *)malloc(ts_pointNmax * sizeof(double));
    par = (int *)malloc(ts_pointNmax * sizeof(int));

    ts_edgeV = (ts_edge *)malloc(ts_edgeNmax * sizeof(ts_edge));
    ts_stackV = (ts_edge **)malloc(ts_edgeNmax * sizeof(ts_edge *));
    ts_eV = (ts_edge **)malloc(2 * ts_edgeNmax * sizeof(ts_edge *));

    pinV = (const Pin **)malloc(termNmax * sizeof(const Pin *));
    termV = (int *)malloc(termNmax * sizeof(int));
    outV = (int *)malloc(termNmax * sizeof(int));

    d = (double *)malloc(dNmax * sizeof(double));
    e = (double *)malloc(dNmax * sizeof(double));
    U = (double **)malloc(dNmax * sizeof(double *));
    U0 = (double *)malloc(dNmax * termNmax * sizeof(double));
    int h;
    for (h = 0; h < dNmax; h++)
      U[h] = U0 + h * termNmax;
  }

  ArnoldiReduce::~ArnoldiReduce()
  {
    free(U0);
    free(U);
    free(e);
    free(d);
    free(outV);
    free(termV);
    free(pinV);
    free(ts_eV);
    free(ts_edgeV);
    free(ts_stackV);
    free(par);
    free(c);
    free(r);
    free(iv);
    free(y);
    free(_u1);
    free(_u0);
    free(ts_pordV);
    free(ts_ordV);
    free(ts_pointV);
  }

  Parasitic *
  ArnoldiReduce::reduceToArnoldi(Parasitic *parasitic,
                                 const Pin *drvr_pin,
                                 float coupling_cap_factor,
                                 const RiseFall *rf,
                                 const OperatingConditions *op_cond,
                                 const Corner *corner,
                                 const MinMax *cnst_min_max,
                                 const ParasiticAnalysisPt *ap)
  {
    parasitic_network_ = reinterpret_cast<ConcreteParasiticNetwork *>(parasitic);
    drvr_pin_ = drvr_pin;
    coupling_cap_factor_ = coupling_cap_factor;
    rf_ = rf;
    op_cond_ = op_cond;
    corner_ = corner;
    cnst_min_max_ = cnst_min_max;
    ap_ = ap;
    loadWork();
    return makeRcmodelDrv();
  }

  void ArnoldiReduce::loadWork(){
    pt_map_.clear();

    int resistor_count = 0;
    ConcreteParasiticDeviceSet devices;
    parasitic_network_->devices(&devices);
    ConcreteParasiticDeviceSet::Iterator device_iter(devices);
    while (device_iter.hasNext()){
      ParasiticDevice *device = device_iter.next();
      if (parasitics_->isResistor(device))
        resistor_count++;
    }

    termN = parasitic_network_->pinNodes()->size();
    int subnode_count = parasitic_network_->subNodes()->size();
    // order: subNode, reservered for driver, pinNode.
    ts_pointN = subnode_count + 1 + termN;
    ts_edgeN = resistor_count;
    allocPoints();
    allocTerms(termN);
    ts_point *p0 = ts_pointV;
    pterm0 = p0 + subnode_count + 1;  // begin of terms in ts_pointV
    ts_point *pend = p0 + ts_pointN;
    ts_point *p;
    ts_edge *e0 = ts_edgeV;
    ts_edge *eend = e0 + ts_edgeN;

    ts_edge *e;
    int tindex;
    for (p = p0; p != pend; p++){
      p->node_ = nullptr;
      p->eN = 0;
      p->is_term = false;
    }
    e = e0;
    int index = 0;
    ConcreteParasiticSubNodeMap::Iterator sub_node_iter(parasitic_network_->subNodes());
    while (sub_node_iter.hasNext()){
      ConcreteParasiticSubNode *node = sub_node_iter.next();
      pt_map_[node] = index;
      p = p0 + index;
      p->node_ = node;
      p->eN = 0;
      p->is_term = false;
      index++;
    }
    pend = pterm0;
    ConcreteParasiticPinNodeMap::Iterator pin_node_iter(parasitic_network_->pinNodes());
    while (pin_node_iter.hasNext()){
      ConcreteParasiticPinNode *node = pin_node_iter.next();
      p = pend++;
      pt_map_[node] = p - p0;
      p->node_ = node;
      p->eN = 0;
      p->is_term = true;
      tindex = p - pterm0;
      p->tindex = tindex;
      const Pin *pin = parasitics_->connectionPin(node);
      pinV[tindex] = pin;
    }

    ts_edge **eV = ts_eV;
    ConcreteParasiticDeviceSet::Iterator device_iter2(devices);
    while (device_iter2.hasNext()){
      ParasiticDevice *device = device_iter2.next();
      if (parasitics_->isResistor(device)){
        ConcreteParasiticResistor *resistor = reinterpret_cast<ConcreteParasiticResistor *>(device);
        ts_point *pt1 = findPt(resistor->node1());
        ts_point *pt2 = findPt(resistor->node2());
        e->from = pt1;
        e->to = pt2;
        e->resistor_ = resistor;
        pt1->eN++;
        if (e->from != e->to)
          pt2->eN++;
        e++;
      }
    }

    for (p = p0; p != pend; p++){
      if (p->node_){
        p->eV = eV;
        eV += p->eN;
        p->eN = 0;
      }
    }
    for (e = e0; e != eend; e++){
      e->from->eV[e->from->eN++] = e;
      if (e->to != e->from)
        e->to->eV[e->to->eN++] = e;
    }
  }

  void
  ArnoldiReduce::allocPoints()
  {
    if (ts_pointN > ts_pointNmax)
    {
      free(par);
      free(c);
      free(r);
      free(iv);
      free(y);
      free(_u1);
      free(_u0);
      free(ts_pordV);
      free(ts_ordV);
      free(ts_pointV);
      ts_pointNmax = ts_pointN + ts_point_count_incr_;
      ts_pointV = (ts_point *)malloc(ts_pointNmax * sizeof(ts_point));
      ts_ordV = (int *)malloc(ts_pointNmax * sizeof(int));
      ts_pordV = (ts_point **)malloc(ts_pointNmax * sizeof(ts_point *));
      _u0 = (double *)malloc(ts_pointNmax * sizeof(double));
      _u1 = (double *)malloc(ts_pointNmax * sizeof(double));
      y = (double *)malloc(ts_pointNmax * sizeof(double));
      iv = (double *)malloc(ts_pointNmax * sizeof(double));
      r = (double *)malloc(ts_pointNmax * sizeof(double));
      c = (double *)malloc(ts_pointNmax * sizeof(double));
      par = (int *)malloc(ts_pointNmax * sizeof(int));
    }
    if (ts_edgeN > ts_edgeNmax)
    {
      free(ts_edgeV);
      free(ts_eV);
      free(ts_stackV);
      ts_edgeNmax = ts_edgeN + ts_edge_count_incr_;
      ts_edgeV = (ts_edge *)malloc(ts_edgeNmax * sizeof(ts_edge));
      ts_stackV = (ts_edge **)malloc(ts_edgeNmax * sizeof(ts_edge *));
      ts_eV = (ts_edge **)malloc(2 * ts_edgeNmax * sizeof(ts_edge *));
    }
  }

  void
  ArnoldiReduce::allocTerms(int nterms)
  {
    if (nterms > termNmax)
    {
      free(U0);
      free(outV);
      free(termV);
      free(pinV);
      termNmax = nterms + 256;
      pinV = (const Pin **)malloc(termNmax * sizeof(const Pin *));
      termV = (int *)malloc(termNmax * sizeof(int));
      outV = (int *)malloc(termNmax * sizeof(int));

      U0 = (double *)malloc(dNmax * termNmax * sizeof(double));
      int h;
      for (h = 0; h < dNmax; h++)
        U[h] = U0 + h * termNmax;
    }
  }

  ts_point * ArnoldiReduce::findPt(ParasiticNode *node){
    return &ts_pointV[pt_map_[reinterpret_cast<ConcreteParasiticNode *>(node)]];
  }

  rcmodel * ArnoldiReduce::makeRcmodelDrv(){
    ParasiticNode *drv_node = parasitics_->findNode(parasitic_network_,drvr_pin_);
    ts_point *pdrv = findPt(drv_node);
    makeRcmodelDfs(pdrv);
    getRC();
    if (ctot_ < 1e-22) // 1e-10ps
      return nullptr;
    setTerms(pdrv);
    makeRcmodelFromTs();
    rcmodel *mod = makeRcmodelFromW();
    return mod;
  }

// pp: point, ee: edge
// make source pp is the source of ee
#define ts_orient(pp, ee) \
  if (ee->from != pp)     \
  {                       \
    ee->to = ee->from;    \
    ee->from = pp;        \
  }

  // Depth first search
  void ArnoldiReduce::makeRcmodelDfs(ts_point *pdrv){
    bool loop = false;
    int k;
    ts_point *p, *q;          // edge: p->q
    ts_point *p0 = ts_pointV;
    ts_point *pend = p0 + ts_pointN;
    for (p = p0; p != pend; p++)
      p->visited = 0;
    ts_edge *e;

    ts_edge **stackV = ts_stackV; // stack of ts_edge voltage
    int stackN = 1;
    stackV[0] = e = pdrv->eV[0];  // driver edge
    ts_orient(pdrv, e); // pdrv -> e
    pdrv->visited = 1;
    pdrv->in_edge = nullptr;
    pdrv->ts = 0;
    ts_ordV[0] = pdrv - p0;
    ts_pordV[0] = pdrv;
    ts_ordN = 1;

    while (stackN > 0){
      e = stackV[stackN - 1];
      q = e->to;

      if (q->visited){
        // if it is a one-rseg self-loop,
        // ignore, and do not even set *loop
        if (e->to != e->from)
          loop = true;
      } else {
        // try to descend
        q->visited = 1;
        q->ts = ts_ordN++;
        ts_pordV[q->ts] = q;
        ts_ordV[q->ts] = q - p0;
        q->in_edge = e;
        if (q->eN > 1){
          for (k = 0; k < q->eN; k++)
            if (q->eV[k] != e)
              break;
          e = q->eV[k];
          ts_orient(q, e);
          stackV[stackN++] = e;
          continue; // descent
        }
      }
      // try to ascend
      while (--stackN >= 0){
        e = stackV[stackN];
        p = e->from;
        // find e in p->eV
        for (k = 0; k < p->eN; k++)
          if (p->eV[k] == e)
            break;
        // if (k==p->eN) notice(0,"ERROR, e not found!\n");
        ++k;
        if (k >= p->eN)
          continue;
        e = p->eV[k];
        // check that next sibling is not the incoming edge
        if (stackN > 0 && e == stackV[stackN - 1]){
          ++k;
          if (k >= p->eN)
            continue;
          e = p->eV[k];
        }
        ts_orient(p, e);
        stackV[stackN++] = e;
        break;
      }
    } // while (stackN)

  }

  // makeRcmodelGetRC
  // collect R & C
  void ArnoldiReduce::getRC(){
    ts_point *p, *p0 = ts_pointV;
    ts_point *pend = p0 + ts_pointN;
    ctot_ = 0.0;
    for (p = p0; p != pend; p++){
      p->c = 0.0;
      p->r = 0.0;
      if (p->node_){
        ParasiticNode *node = p->node_;
        double cap = parasitics_->nodeGndCap(node, ap_) + pinCapacitance(node);
        if (cap > 0.0){
          p->c = cap;
          ctot_ += cap;
        }else
          p->c = 0.0;
        if (p->in_edge && p->in_edge->resistor_)
          p->r = parasitics_->value(p->in_edge->resistor_, ap_);
      }
    }
  }

  // cap of a pin
  float ArnoldiReduce::pinCapacitance(ParasiticNode *node){
    const Pin *pin = parasitics_->connectionPin(node);
    float pin_cap = 0.0;
    if (pin){
      Port *port = network_->port(pin);
      LibertyPort *lib_port = network_->libertyPort(port);
      if (lib_port)
        pin_cap = sdc_->pinCapacitance(pin, rf_, op_cond_, corner_, cnst_min_max_);
      else if (network_->isTopLevelPort(pin))
        pin_cap = sdc_->portExtCap(port, rf_, corner_, cnst_min_max_);
    }
    return pin_cap;
  }

  void ArnoldiReduce::setTerms(ts_point *pdrv){
    // termV: from drv-ordered to fixed order
    // outV:  from drv-ordered to ts_pordV
    ts_point *p;
    int k, k0;
    termV[0] = k0 = pdrv->tindex;
    for (k = 1; k < termN; k++){
      if (k == k0)
        termV[k] = 0;
      else
        termV[k] = k;
    }
    for (k = 0; k < termN; k++){
      p = pterm0 + termV[k];
      outV[k] = p->ts;
    }
  }

  // The guts of the arnoldi reducer.
  // Check Arnoldi.txt
//   U0 = (1,1,..1)/sqrt(sum C)
//   representing the initial value of V, V[j] = sqrt(n)U0[j] at t=0.
//   sum(C) = C[0]+..C[n-1], so U0.C U0 = 1.
// Let:
//   W = R C U0
//   d0 = U0.C W
//   W' = W - d0 U0
//   e0 = sqrt(W'.C W')
//   U1 = W'/e0
// Then:  U0.C U0 = U1.C U1 = 1, U0.C U1 = 0, and
//   R C U0 = d0 U0 + e0 U1
// Next step:
//   W = R C U1
//   d1 = U1.C W
//   W' = W - d1 U1 - e0 U0
//   e1 = sqrt(W'.C W')
//   U2 = W'/e1
// and we have U2.C U2 = 1, U2.C U1 = U2.C U0 = 0, and
//   RC U1 = e0 U0 + d1 U1 + e1 U2
// NOTE： We should perform Arnoldi to A=-inv(G)*C. Here, we do it for inv(G), therefore, the pole computed are negative. 
// Why, G = Ag * diag(gi) * Ag', why inv(G) = R = diag(ri)
  void ArnoldiReduce::makeRcmodelFromTs() {
    ts_point *p, *p0 = ts_pointV;
    int n = ts_ordN;
    int nterms = termN;
    int i, j, k, h;
    int max_order = 5;

    double *u0, *u1;
    u0 = _u0;
    u1 = _u1;
    double sum, e1;
    order = max_order;
    if (n < order)
      order = n;

    par[0] = -1;
    r[0] = 0.0;
    c[0] = ts_pordV[0]->c;
    for (j = 1; j < n; j++){
      p = ts_pordV[j];
      c[j] = p->c; // cap
      r[j] = p->r; // resistor
      par[j] = p->in_edge->from->ts; // resistor from node
    }

    sum = 0.0;
    for (j = 0; j < n; j++)
      sum += c[j];
    ctot_ = sum;
    sqc_ = sqrt(sum);
    double sqrt_ctot_inv = 1.0 / sqc_;
    for (j = 0; j < n; j++)
      u0[j] = sqrt_ctot_inv;

    for (h = 0; h < order; h++){
      for (i = 0; i < nterms; i++){
        U[h][i] = u0[outV[i]];
      }

      // Compute inv(G)Cu0, let Cu0=b. 
      // Gx = b. Do the LU decomposition. G = L*L', 
      // where L is the incidence matrix * diag(1/sqrt(ri)), the indidence matrix is upper matrix (by placing resistance ri before node i. )
      // Ly=b, L'x = y; iv is y and y is x here.
      // y = R C u0  (W)
      for (j = 0; j < n; j++){
        iv[j] = 0.0;
      }
      for (j = n - 1; j > 0; j--){
        iv[j] += c[j] * u0[j];
        iv[par[j]] += iv[j];
      }
      iv[0] += c[0] * u0[0];
      y[0] = 0.0;
      for (j = 1; j < n; j++){
        y[j] = y[par[j]] + r[j] * iv[j]; // resistor from -> to ?
      }

      // d[h] = u0 C y (d0)
      sum = 0.0;
      for (j = 1; j < n; j++){
        sum += u0[j] * c[j] * y[j];
      }
      d[h] = sum;
      if (h == order - 1)
        break;
      if (d[h] < 1e-13){ // .1ps
        order = h + 1;
        break;
      }

      // y = y - d[h]*u0 - e[h-1]*u1  (W')
      if (h == 0){
        for (j = 0; j < n; j++)
          y[j] -= sum * u0[j];
      }else{
        e1 = e[h - 1];
        for (j = 0; j < n; j++)
          y[j] -= sum * u0[j] + e1 * u1[j];
      }

      // e[h] = sqrt(y C y)  (e)
      // u1 = y/e[h]         (u)
      sum = 0.0;
      for (j = 0; j < n; j++){
        sum += c[j] * y[j] * y[j];
      }
      if (sum < 1e-30){ // (1e-6ns)^2
        order = h + 1;
        break;
      }
      e[h] = sqrt(sum);
      sum = 1.0 / e[h];
      for (j = 0; j < n; j++)
        u1[j] = sum * y[j];

      // swap u0, u1
      if (h % 2){
        u0 = _u0;
        u1 = _u1;
      }else{
        u0 = _u1;
        u1 = _u0;
      }
    }
  }

  // Build rcmodel from calculation results
  rcmodel *
  ArnoldiReduce::makeRcmodelFromW()
  {
    int j, h;
    int n = termN;
    rcmodel *mod = new rcmodel();
    mod->order = order;
    mod->n = n;
    if (order > 0){
      int totd = order + order - 1 + order * n;
      mod->d = (double *)malloc(totd * sizeof(double));
      if (order > 1)
        mod->e = mod->d + order;
      else
        mod->e = nullptr;
      mod->U = (double **)malloc(order * sizeof(double *));
      mod->U[0] = mod->d + order + order - 1;
      for (h = 1; h < order; h++)
        mod->U[h] = mod->U[0] + h * n;
      for (h = 0; h < order; h++){
        mod->d[h] = d[h];
        if (h < order - 1)
          mod->e[h] = e[h];
        for (j = 0; j < n; j++)
          mod->U[h][j] = U[h][j];
      }
    }

    mod->pinV = (const Pin **)malloc(n * sizeof(const Pin *));
    for (j = 0; j < n; j++){
      int k = termV[j];
      mod->pinV[j] = pinV[k];
    }

    mod->ctot = ctot_;
    mod->sqc = sqc_;
    return mod;
  }

} // namespace
