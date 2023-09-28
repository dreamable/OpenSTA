


#include <string>

#include "MinMax.hh"
#include "LibertyClass.hh"
#include "NetworkClass.hh"
#include "Delay.hh"
#include "ParasiticsClass.hh"
#include "StaState.hh"

namespace sta {

using std::string;

class Parasitic;
class DcalcAnalysisPt;

// Delay calculator class hierarchy.
//  ArcDelayCalc
//   UnitDelayCalc
//   LumpedCapDelayCalc
//    RCDelayCalc
//     SlewDegradeDelayCalc
//     DmpCeffDelayCalc
//      DmpCeffElmoreDelayCalc
//      DmpCeffTwoPoleDelayCalc
//     ArnoldiDelayCalc

// Abstract class to interface to a delay calculator primitive.
class ArcDelayCalc : public StaState
{
public:
  explicit ArcDelayCalc(StaState *sta);
  virtual ~ArcDelayCalc() {}
  virtual ArcDelayCalc *copy() = 0;

  // Find the parasitic for drvr_pin that is acceptable to the delay
  // calculator by probing parasitics_.
  virtual Parasitic *findParasitic(const Pin *drvr_pin,
				   const RiseFall *rf,
				   const DcalcAnalysisPt *dcalc_ap) = 0;
  virtual ReducedParasiticType reducedParasiticType() const = 0;
  // Find the wire delays and slews for an input port without a driving cell.
  // This call primarily initializes the load delay/slew iterator.
  virtual void inputPortDelay(const Pin *port_pin,
			      float in_slew,
			      const RiseFall *rf,
			      const Parasitic *parasitic,
			      const DcalcAnalysisPt *dcalc_ap) = 0;

  // Find the delay and slew for arc driving drvr_pin.
  virtual void gateDelay(const LibertyCell *drvr_cell,
			 const TimingArc *arc,
			 const Slew &in_slew,
			 // Pass in load_cap or drvr_parasitic.
			 float load_cap,
			 const Parasitic *drvr_parasitic,
			 float related_out_cap,
			 const Pvt *pvt,
			 const DcalcAnalysisPt *dcalc_ap,
			 // Return values.
			 ArcDelay &gate_delay,
			 Slew &drvr_slew) = 0;
  // Find the wire delay and load slew of a load pin.
  // Called after inputPortDelay or gateDelay.
  virtual void loadDelay(const Pin *load_pin,
			 // Return values.
			 ArcDelay &wire_delay,
			 Slew &load_slew) = 0;
  virtual void setMultiDrvrSlewFactor(float factor) = 0;
  // Ceff for parasitics with pi models.
  virtual float ceff(const LibertyCell *drvr_cell,
		     const TimingArc *arc,
		     const Slew &in_slew,
		     float load_cap,
		     const Parasitic *drvr_parasitic,
		     float related_out_cap,
		     const Pvt *pvt,
		     const DcalcAnalysisPt *dcalc_ap) = 0;

  // Find the delay for a timing check arc given the arc's
  // from/clock, to/data slews and related output pin parasitic.
  virtual void checkDelay(const LibertyCell *drvr_cell,
			  const TimingArc *arc,
			  const Slew &from_slew,
			  const Slew &to_slew,
			  float related_out_cap,
			  const Pvt *pvt,
			  const DcalcAnalysisPt *dcalc_ap,
			  // Return values.
			  ArcDelay &margin) = 0;
  // Report delay and slew calculation.
  virtual string reportGateDelay(const LibertyCell *drvr_cell,
                                 const TimingArc *arc,
                                 const Slew &in_slew,
                                 // Pass in load_cap or drvr_parasitic.
                                 float load_cap,
                                 const Parasitic *drvr_parasitic,
                                 float related_out_cap,
                                 const Pvt *pvt,
                                 const DcalcAnalysisPt *dcalc_ap,
                                 int digits) = 0;
  // Report timing check delay calculation.
  virtual string reportCheckDelay(const LibertyCell *cell,
                                  const TimingArc *arc,
                                  const Slew &from_slew,
                                  const char *from_slew_annotation,
                                  const Slew &to_slew,
                                  float related_out_cap,
                                  const Pvt *pvt,
                                  const DcalcAnalysisPt *dcalc_ap,
                                  int digits) = 0;
  virtual void finishDrvrPin() = 0;

protected:
  GateTimingModel *gateModel(const TimingArc *arc,
			     const DcalcAnalysisPt *dcalc_ap) const;
  CheckTimingModel *checkModel(const TimingArc *arc,
			       const DcalcAnalysisPt *dcalc_ap) const;
  TimingModel *model(const TimingArc *arc,
		     const DcalcAnalysisPt *dcalc_ap) const;
};

} // namespace
