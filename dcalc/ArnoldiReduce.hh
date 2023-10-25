

// (c) 2018 Nefelus, Inc.
//
// Author: W. Scott

#include "Map.hh"
#include "Transition.hh"
#include "NetworkClass.hh"
#include "ParasiticsClass.hh"
#include "SdcClass.hh"
#include "StaState.hh"

namespace sta
{

  class ConcreteParasiticNetwork;
  class ConcreteParasiticNode;
  class Corner;

  class rcmodel;
  struct ts_edge;
  struct ts_point;

  typedef Map<ConcreteParasiticNode *, int> ArnolidPtMap;

  // ts: timing stack?
  struct ts_point{
    ParasiticNode *node_;
    bool is_term; // is pinNode or not (subNode)
    int tindex;   // index into termV of corresponding term (order in pinNodes)
    int eN;       // # of ts_edge
    ts_edge **eV; // edge vector, ts_edge[eN]
    bool visited; // DFS flag
    ts_edge *in_edge; // coming edge
    int ts;     // index of stack? 
    double c;   // capacitance 
    double r;   // resistance
  };

  struct ts_edge{
    ConcreteParasiticResistor *resistor_;
    ts_point *from;
    ts_point *to;
  };

  class ArnoldiReduce : public StaState
  {
  public:
    ArnoldiReduce(StaState *sta);
    ~ArnoldiReduce();
    Parasitic *reduceToArnoldi(Parasitic *parasitic,
                               const Pin *drvr_pin,
                               float coupling_cap_factor,
                               const RiseFall *rf,
                               const OperatingConditions *op_cond,
                               const Corner *corner,
                               const MinMax *cnst_min_max,
                               const ParasiticAnalysisPt *ap);

  protected:
    void loadWork();
    rcmodel *makeRcmodelDrv();
    void allocPoints();
    void allocTerms(int nterms);
    ts_point *findPt(ParasiticNode *node);
    void makeRcmodelDfs(ts_point *pdrv);
    void getRC();
    float pinCapacitance(ParasiticNode *node);
    void setTerms(ts_point *pdrv);
    void makeRcmodelFromTs();
    rcmodel *makeRcmodelFromW();

    ConcreteParasiticNetwork *parasitic_network_;
    const Pin *drvr_pin_;
    float coupling_cap_factor_;
    const RiseFall *rf_;
    const OperatingConditions *op_cond_;
    const Corner *corner_;
    const MinMax *cnst_min_max_;
    const ParasiticAnalysisPt *ap_;

    // ParasiticNode -> ts_point index.
    ArnolidPtMap pt_map_; // ParasiticNode -> ts_points

    // rcWork
    int ts_pointN;    // = pins +subnodes +1  
    int ts_pointNmax; // upper bound of pin number
    static const int ts_point_count_incr_; // 1024, if ts_pointN > ts_pointNMax, increase it by
    ts_point *ts_pointV; // all ts_points, ts_points[ts_pointNmax]. The order is subnode, driver, pinNode

    int ts_edgeN;     // = # of R
    int ts_edgeNmax;  // upper bound of edge number
    static const int ts_edge_count_incr_; // 1024, increase ts_edgeNmax if < ts_edgeN
    ts_edge *ts_edgeV; // all ts_edges, ts_edge[ts_edgeNmax]
    ts_edge **ts_eV;   // edge vector, ts_edge*[ts_edgeNMax]
    ts_edge **ts_stackV;  // ts_edge*[ts_edgeNMax]

    ts_point **ts_pordV; // point order vector, ts_point*[ts_pointNmax]
    int *ts_ordV;  // order vector, int[ts_pointNmax], index in ts_points
    int ts_ordN;   //

    int termNmax;     // upper bound of term 
    int termN;        // # of pins
    ts_point *pterm0; // start position of pinNodes in ts_pointV
    const Pin **pinV; // pin vector, fixed order, offset from pterm0, ts_point index -> Pin
    int *termV;       // from drv-ordered to fixed order
    int *outV;        // from drv-ordered to ts_pordV


    // Hq  and Uq matrix
    int dNmax;
    double *d;
    double *e;
    double *U0;
    double **U;

    // parameter for arnoldi algorithm
    double ctot_;
    double sqc_;
    double *_u0, *_u1; // current u, next u
    double *y, *iv;   
    double *c, *r;
    int *par;
    int order;
  };

} // namespace
