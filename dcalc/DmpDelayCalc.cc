

#include "DmpDelayCalc.hh"

#include "TableModel.hh"
#include "TimingArc.hh"
#include "Liberty.hh"
#include "Sdc.hh"
#include "Parasitics.hh"
#include "DcalcAnalysisPt.hh"
#include "GraphDelayCalc.hh"
#include "DmpCeff.hh"
#include "Network.hh"

namespace sta {

////////////////////////////////////////////////////////////////

bool DmpCeffDelayCalc::unsuppored_model_warned_ = false;

DmpCeffDelayCalc::DmpCeffDelayCalc(StaState *sta) :
  RCDelayCalc(sta),
  dmp_cap_(new DmpCap(sta)),
  dmp_pi_(new DmpPi(sta)),
  dmp_zero_c2_(new DmpZeroC2(sta)),
  dmp_alg_(nullptr)
{
}

DmpCeffDelayCalc::~DmpCeffDelayCalc()
{
  delete dmp_cap_;
  delete dmp_pi_;
  delete dmp_zero_c2_;
}

void
DmpCeffDelayCalc::inputPortDelay(const Pin *port_pin,
				 float in_slew,
				 const RiseFall *rf,
				 const Parasitic *parasitic,
				 const DcalcAnalysisPt *dcalc_ap)
{
  dmp_alg_ = nullptr;
  RCDelayCalc::inputPortDelay(port_pin, in_slew, rf, parasitic, dcalc_ap);
}

void
DmpCeffDelayCalc::gateDelay(const LibertyCell *drvr_cell,
			    const TimingArc *arc,
			    const Slew &in_slew,
			    float load_cap,
			    const Parasitic *drvr_parasitic,
			    float related_out_cap,
			    const Pvt *pvt,
			    const DcalcAnalysisPt *dcalc_ap,
			    // Return values.
			    ArcDelay &gate_delay,
			    Slew &drvr_slew){
  input_port_ = false;
  drvr_rf_ = arc->toEdge()->asRiseFall();
  drvr_library_ = drvr_cell->libertyLibrary();
  drvr_parasitic_ = drvr_parasitic;
  GateTimingModel *model = gateModel(arc, dcalc_ap);
  GateTableModel *table_model = dynamic_cast<GateTableModel*>(model);
  if (table_model && drvr_parasitic) {
    float in_slew1 = delayAsFloat(in_slew);
    float c2, rpi, c1;
    parasitics_->piModel(drvr_parasitic, c2, rpi, c1);
    setCeffAlgorithm(drvr_library_, drvr_cell, pvt, table_model,drvr_rf_, in_slew1, related_out_cap,c2, rpi, c1);
    double dmp_gate_delay, dmp_drvr_slew;
    gateDelaySlew(dmp_gate_delay, dmp_drvr_slew);
    gate_delay = dmp_gate_delay;
    drvr_slew = dmp_drvr_slew;
  }else {
    LumpedCapDelayCalc::gateDelay(drvr_cell, arc, in_slew, load_cap,drvr_parasitic, related_out_cap, pvt,dcalc_ap, gate_delay, drvr_slew);
    if (drvr_parasitic && !unsuppored_model_warned_) {
      unsuppored_model_warned_ = true;
      report_->warn(1, "cell %s delay model not supported on SPF parasitics by DMP delay calculator",drvr_cell->name());
    }
  }
  drvr_slew_ = drvr_slew;
  multi_drvr_slew_factor_ = 1.0F;
}

void
DmpCeffDelayCalc::setCeffAlgorithm(const LibertyLibrary *drvr_library,
				   const LibertyCell *drvr_cell,
				   const Pvt *pvt,
				   const GateTableModel *gate_model,
				   const RiseFall *rf,
				   double in_slew,
				   float related_out_cap,
				   double c2,
				   double rpi,
				   double c1){
  double rd = 0.0;
  if (gate_model) {
    rd = gateModelRd(drvr_cell, gate_model, rf, in_slew, c2, c1,related_out_cap, pvt, pocv_enabled_);
    if (rd < 1e-2  // Zero Rd means the table is constant and thus independent of load cap.
	      || rpi < rd * 1e-3 	// Rpi is small compared to Rd, which makes the load capacitive.
	      || (c1 == 0.0 || c1 < c2 * 1e-3 || rpi == 0.0))	// c1/Rpi can be ignored.
      dmp_alg_ = dmp_cap_;
    else if (c2 < c1 * 1e-3)
      dmp_alg_ = dmp_zero_c2_;
    else
      dmp_alg_ = dmp_pi_;       // The full monty.
  }else{
    dmp_alg_ = dmp_cap_;
  }
  dmp_alg_->init(drvr_library, drvr_cell, pvt, gate_model, drvr_rf_, rd, in_slew, related_out_cap, c2, rpi, c1);
}

float
DmpCeffDelayCalc::ceff(const LibertyCell *drvr_cell,
		       const TimingArc *arc,
		       const Slew &in_slew,
		       float load_cap,
		       const Parasitic *drvr_parasitic,
		       float related_out_cap,
		       const Pvt *pvt,
		       const DcalcAnalysisPt *dcalc_ap)
{
  ArcDelay gate_delay;
  Slew drvr_slew;
  gateDelay(drvr_cell, arc, in_slew, load_cap,drvr_parasitic, related_out_cap, pvt, dcalc_ap,gate_delay, drvr_slew);
  if (dmp_alg_)
    return dmp_alg_->ceff();
  else
    return load_cap;
}

string
DmpCeffDelayCalc::reportGateDelay(const LibertyCell *drvr_cell,
				  const TimingArc *arc,
				  const Slew &in_slew,
				  float load_cap,
				  const Parasitic *drvr_parasitic,
				  float related_out_cap,
				  const Pvt *pvt,
				  const DcalcAnalysisPt *dcalc_ap,
				  int digits)
{
  ArcDelay gate_delay;
  Slew drvr_slew;
  gateDelay(drvr_cell, arc, in_slew, load_cap,drvr_parasitic, related_out_cap, pvt, dcalc_ap,gate_delay, drvr_slew);
  GateTimingModel *model = gateModel(arc, dcalc_ap);
  float c_eff = 0.0;
  string result;
  if (drvr_parasitic_ && dmp_alg_) {
    c_eff = dmp_alg_->ceff();
    const LibertyLibrary *drvr_library = drvr_cell->libertyLibrary();
    const Units *units = drvr_library->units();
    const Unit *cap_unit = units->capacitanceUnit();
    const Unit *res_unit = units->resistanceUnit();
    float c2, rpi, c1;
    parasitics_->piModel(drvr_parasitic_, c2, rpi, c1);
    result += "Pi model C2=";
    result += cap_unit->asString(c2, digits);
    result += " Rpi=";
    result += res_unit->asString(rpi, digits);
    result += " C1=";
    result += cap_unit->asString(c1, digits);
    result += ", Ceff=";
    result += cap_unit->asString(c_eff, digits);
    result += '\n';
  }else{
    c_eff = load_cap;
  }
  if (model) {
    float in_slew1 = delayAsFloat(in_slew);
    result += model->reportGateDelay(drvr_cell, pvt, in_slew1, c_eff,related_out_cap, pocv_enabled_, digits);
  }
  return result;
}


void
DmpCeffDelayCalc::gateDelaySlew(double &delay,double &slew){
  dmp_alg_->gateDelaySlew(delay, slew);
}

void
DmpCeffDelayCalc::loadDelaySlew(const Pin *load_pin,double elmore,ArcDelay &delay,Slew &slew){
  if (dmp_alg_)
    dmp_alg_->loadDelaySlew(load_pin, elmore, delay, slew);
}

// Notify algorithm components.
void
DmpCeffDelayCalc::copyState(const StaState *sta)
{
  StaState::copyState(sta);
  dmp_cap_->copyState(sta);
  dmp_pi_->copyState(sta);
  dmp_zero_c2_->copyState(sta);
}

////////////////////////////////////////////////////////////////

ArcDelayCalc *
makeDmpCeffElmoreDelayCalc(StaState *sta)
{
  return new DmpCeffElmoreDelayCalc(sta);
}

DmpCeffElmoreDelayCalc::DmpCeffElmoreDelayCalc(StaState *sta) :
  DmpCeffDelayCalc(sta)
{
}

ArcDelayCalc *
DmpCeffElmoreDelayCalc::copy()
{
  return new DmpCeffElmoreDelayCalc(this);
}

void
DmpCeffElmoreDelayCalc::gateDelay(const LibertyCell *drvr_cell,
				  const TimingArc *arc,
				  const Slew &in_slew,
				  float load_cap,
				  const Parasitic *drvr_parasitic,
				  float related_out_cap,
				  const Pvt *pvt,
				  const DcalcAnalysisPt *dcalc_ap,
				  // Return values.
				  ArcDelay &gate_delay,
				  Slew &drvr_slew)
{
  DmpCeffDelayCalc::gateDelay(drvr_cell, arc, in_slew,
			      load_cap, drvr_parasitic, related_out_cap,
			      pvt, dcalc_ap,
			      gate_delay, drvr_slew);
}

void DmpCeffElmoreDelayCalc::loadDelay(const Pin *load_pin, ArcDelay &wire_delay,Slew &load_slew) {
  ArcDelay wire_delay1 = 0.0;
 Slew load_slew1 = drvr_slew_;
  bool elmore_exists = false;
  float elmore = 0.0;
  if (drvr_parasitic_)
    parasitics_->findElmore(drvr_parasitic_, load_pin, elmore, elmore_exists);
  if (elmore_exists) {
    if (input_port_) {
      // Input port with no external driver.
      if (parasitics_->isReducedParasiticNetwork(drvr_parasitic_))
	      dspfWireDelaySlew(load_pin, elmore, wire_delay1, load_slew1);
      else {
        // The elmore delay on an input port is used for the wire
        // delay and the load slew is the same as the driver slew.
        wire_delay1 = elmore;
        load_slew1 = drvr_slew_;
      }
    }else{
      loadDelaySlew(load_pin, elmore, wire_delay1, load_slew1);
    }
  }
  thresholdAdjust(load_pin, wire_delay1, load_slew1);
  wire_delay = wire_delay1;
  load_slew = load_slew1 * multi_drvr_slew_factor_;
}

////////////////////////////////////////////////////////////////

ArcDelayCalc *
makeDmpCeffTwoPoleDelayCalc(StaState *sta)
{
  return new DmpCeffTwoPoleDelayCalc(sta);
}

DmpCeffTwoPoleDelayCalc::DmpCeffTwoPoleDelayCalc(StaState *sta) :
  DmpCeffDelayCalc(sta),
  parasitic_is_pole_residue_(false),
  vth_(0.0),
  vl_(0.0),
  vh_(0.0),
  slew_derate_(0.0)
{
}

ArcDelayCalc *
DmpCeffTwoPoleDelayCalc::copy()
{
  return new DmpCeffTwoPoleDelayCalc(this);
}

Parasitic * DmpCeffTwoPoleDelayCalc::findParasitic(const Pin *drvr_pin,const RiseFall *rf,const DcalcAnalysisPt *dcalc_ap){
  const Corner *corner = dcalc_ap->corner();
  // set_load has precidence over parasitics.
  if (!sdc_->drvrPinHasWireCap(drvr_pin, corner)) {
    Parasitic *parasitic = nullptr;
    const ParasiticAnalysisPt *parasitic_ap = dcalc_ap->parasiticAnalysisPt();
    if (parasitics_->haveParasitics()) {
      // Prefer PiPoleResidue.
      parasitic = parasitics_->findPiPoleResidue(drvr_pin, rf,parasitic_ap);
      if (parasitic) return parasitic;

      parasitic = parasitics_->findPiElmore(drvr_pin, rf, parasitic_ap);
      if (parasitic) return parasitic;

      Parasitic *parasitic_network = parasitics_->findParasiticNetwork(drvr_pin, parasitic_ap);
      if (parasitic_network) {
	      parasitics_->reduceToPiPoleResidue2(parasitic_network, drvr_pin,dcalc_ap->operatingConditions(),corner,dcalc_ap->constraintMinMax(),parasitic_ap);
	      parasitic = parasitics_->findPiPoleResidue(drvr_pin, rf, parasitic_ap);
	      reduced_parasitic_drvrs_.push_back(drvr_pin);
	      return parasitic;
      }
    }

    const MinMax *cnst_min_max = dcalc_ap->constraintMinMax();
    Wireload *wireload = sdc_->wireload(cnst_min_max);
    if (wireload) {
      float pin_cap, wire_cap, fanout;
      bool has_wire_cap;
      graph_delay_calc_->netCaps(drvr_pin, rf, dcalc_ap,pin_cap, wire_cap, fanout, has_wire_cap);
      parasitic = parasitics_->estimatePiElmore(drvr_pin, rf, wireload,fanout, pin_cap,dcalc_ap->operatingConditions(),corner,cnst_min_max,parasitic_ap);
      // Estimated parasitics are not recorded in the "database", so
      // it for deletion after the drvr pin delay calc is finished.
      if (parasitic)
	      unsaved_parasitics_.push_back(parasitic);
      return parasitic;
    }
  }
  return nullptr;
}

ReducedParasiticType
DmpCeffTwoPoleDelayCalc::reducedParasiticType() const
{
  return ReducedParasiticType::pi_pole_residue2;
}

void
DmpCeffTwoPoleDelayCalc::inputPortDelay(const Pin *port_pin,
					float in_slew,
					const RiseFall *rf,
					const Parasitic *parasitic,
					const DcalcAnalysisPt *dcalc_ap)
{
  parasitic_is_pole_residue_ = parasitics_->isPiPoleResidue(parasitic);
  DmpCeffDelayCalc::inputPortDelay(port_pin, in_slew, rf, parasitic, dcalc_ap);
}

void DmpCeffTwoPoleDelayCalc::gateDelay(const LibertyCell *drvr_cell,
				   const TimingArc *arc,
				   const Slew &in_slew,
				   float load_cap,
				   const Parasitic *drvr_parasitic,
				   float related_out_cap,
				   const Pvt *pvt,
				   const DcalcAnalysisPt *dcalc_ap,
				   // Return values.
				   ArcDelay &gate_delay,
				   Slew &drvr_slew){
  parasitic_is_pole_residue_ = parasitics_->isPiPoleResidue(drvr_parasitic);
  const LibertyLibrary *drvr_library = drvr_cell->libertyLibrary();
  const RiseFall *rf = arc->toEdge()->asRiseFall();
  vth_ = drvr_library->outputThreshold(rf);
  vl_ = drvr_library->slewLowerThreshold(rf);
  vh_ = drvr_library->slewUpperThreshold(rf);
  slew_derate_ = drvr_library->slewDerateFromLibrary();
  DmpCeffDelayCalc::gateDelay(drvr_cell, arc, in_slew,load_cap, drvr_parasitic,related_out_cap, pvt, dcalc_ap,gate_delay, drvr_slew);
}

void DmpCeffTwoPoleDelayCalc::loadDelay(const Pin *load_pin, ArcDelay &wire_delay,Slew &load_slew){
  // Should handle PiElmore parasitic.
  ArcDelay wire_delay1 = 0.0;
  Slew load_slew1 = drvr_slew_;
  Parasitic *pole_residue = 0;
  if (parasitic_is_pole_residue_)
    pole_residue = parasitics_->findPoleResidue(drvr_parasitic_, load_pin);
  if (pole_residue) {
    size_t pole_count = parasitics_->poleResidueCount(pole_residue);
    if (pole_count >= 1) {
      ComplexFloat pole1, residue1;
      // Find the 1st (elmore) pole.
      parasitics_->poleResidue(pole_residue, 0, pole1, residue1);
      if (pole1.imag() == 0.0 && residue1.imag() == 0.0) {
        float p1 = pole1.real();
        float k1 = residue1.real();
        if (input_port_) {
          float elmore = 1.0F / p1;
          // Input port with no external driver.
          if (parasitics_->isReducedParasiticNetwork(drvr_parasitic_))
            dspfWireDelaySlew(load_pin, elmore, wire_delay1, load_slew1);
          else {
            // For RSPF on an input port the elmore delay is used for the
            // wire delay and the load slew is the same as the driver slew.
            wire_delay1 = elmore;
            load_slew1 = drvr_slew_;
          }
        }else {
          if (pole_count >= 2)
            loadDelay(pole_residue, p1, k1, wire_delay1, load_slew1);
          else {
            float elmore = 1.0F / p1;
            wire_delay1 = elmore;
            load_slew1 = drvr_slew_;
          }
        }
      }
    }
  }
  thresholdAdjust(load_pin, wire_delay1, load_slew1);
  wire_delay = wire_delay1;
  load_slew = load_slew1 * multi_drvr_slew_factor_;
}

void
DmpCeffTwoPoleDelayCalc::loadDelay(Parasitic *pole_residue,
				   double p1, double k1,
				   ArcDelay &wire_delay,
				   Slew &load_slew)
{
  ComplexFloat pole2, residue2;
  parasitics_->poleResidue(pole_residue, 1, pole2, residue2);
  if (!delayZero(drvr_slew_)&& pole2.imag() == 0.0&& residue2.imag() == 0.0) {
    double p2 = pole2.real();
    double k2 = residue2.real();
    double k1_p1_2 = k1 / (p1 * p1);
    double k2_p2_2 = k2 / (p2 * p2);
    double B = k1_p1_2 + k2_p2_2;
    // Convert tt to 0:1 range.
    float tt = delayAsFloat(drvr_slew_) * slew_derate_ / (vh_ - vl_);
    double y_tt = (tt - B + k1_p1_2 * exp(-p1 * tt)+ k2_p2_2 * exp(-p2 * tt)) / tt;
    wire_delay = loadDelay(vth_, p1, p2, k1, k2, B, k1_p1_2, k2_p2_2, tt, y_tt)- tt * vth_;
    float tl = loadDelay(vl_, p1, p2, k1, k2, B, k1_p1_2, k2_p2_2, tt, y_tt);
    float th = loadDelay(vh_, p1, p2, k1, k2, B, k1_p1_2, k2_p2_2, tt, y_tt);
    load_slew = (th - tl) / slew_derate_;
  }
}

float
DmpCeffTwoPoleDelayCalc::loadDelay(double vth,
				   double p1,
				   double p2,
				   double k1,
				   double k2,
				   double B,
				   double k1_p1_2,
				   double k2_p2_2,
				   double tt,
				   double y_tt)
{
  if (y_tt < vth) {
    // t1 > tt
    // Initial guess.
    double t1 = log(k1 * (exp(p1 * tt) - 1.0) / ((1.0 - vth) * p1 * p1 * tt))/p1;
    // Take one newton-raphson step.
    double exp_p1_t1 = exp(-p1 * t1);
    double exp_p2_t1 = exp(-p2 * t1);
    double exp_p1_t1_tt = exp(-p1 * (t1 - tt));
    double exp_p2_t1_tt = exp(-p2 * (t1 - tt));
    double y_t1 = (tt - k1_p1_2 * (exp_p1_t1_tt - exp_p1_t1) - k2_p2_2 * (exp_p2_t1_tt - exp_p2_t1)) / tt;
    double yp_t1 = (k1 / p1 * (exp_p1_t1_tt - exp_p1_t1) - k2 / p2 * (exp_p2_t1_tt - exp_p2_t1)) / tt;
    double delay = t1 - (y_t1 - vth) / yp_t1;
    return static_cast<float>(delay);
  }else {
    // t1 < tt
    // Initial guess based on y(tt).
    double t1 = vth * tt / y_tt;
    // Take one newton-raphson step.
    double exp_p1_t1 = exp(-p1 * t1);
    double exp_p2_t1 = exp(-p2 * t1);
    double y_t1 = (t1 - B + k1_p1_2 * exp_p1_t1+ k2_p2_2 * exp_p1_t1) / tt;
    double yp_t1 = (1 - k1 / p1 * exp_p1_t1- k2 / p2 * exp_p2_t1) / tt;
    double delay = t1 - (y_t1 - vth) / yp_t1;
    return static_cast<float>(delay);
  }
}

} // namespace
