



#include "ArcDelayCalc.hh"

namespace sta {

// Liberty table model lumped capacitance arc delay calculator.
// Wire delays are zero.
class LumpedCapDelayCalc : public ArcDelayCalc
{
public:
  LumpedCapDelayCalc(StaState *sta);
  ArcDelayCalc *copy() override;
  Parasitic *findParasitic(const Pin *drvr_pin,
                           const RiseFall *rf,
                           const DcalcAnalysisPt *dcalc_ap) override;
  ReducedParasiticType reducedParasiticType() const override;
  void inputPortDelay(const Pin *port_pin,
                      float in_slew,
                      const RiseFall *rf,
                      const Parasitic *parasitic,
                      const DcalcAnalysisPt *dcalc_ap) override;
  void gateDelay(const LibertyCell *drvr_cell,
                 const TimingArc *arc,
                 const Slew &in_slew,
                 float load_cap,
                 const Parasitic *drvr_parasitic,
                 float related_out_cap,
                 const Pvt *pvt,
                 const DcalcAnalysisPt *dcalc_ap,
                 // Return values.
                 ArcDelay &gate_delay,
                 Slew &drvr_slew) override;
  void setMultiDrvrSlewFactor(float factor) override;
  float ceff(const LibertyCell *drvr_cell,
             const TimingArc *arc,
             const Slew &in_slew,
             float load_cap,
             const Parasitic *drvr_parasitic,
             float related_out_cap,
             const Pvt *pvt,
             const DcalcAnalysisPt *dcalc_ap) override;
  void loadDelay(const Pin *load_pin,
                 // Return values.
                 ArcDelay &wire_delay,
                 Slew &load_slew) override;
  void checkDelay(const LibertyCell *cell,
                  const TimingArc *arc,
                  const Slew &from_slew,
                  const Slew &to_slew,
                  float related_out_cap,
                  const Pvt *pvt,
                  const DcalcAnalysisPt *dcalc_ap,
                  // Return values.
                  ArcDelay &margin) override;
  string reportGateDelay(const LibertyCell *drvr_cell,
                         const TimingArc *arc,
                         const Slew &in_slew,
                         float load_cap,
                         const Parasitic *drvr_parasitic,
                         float related_out_cap,
                         const Pvt *pvt,
                         const DcalcAnalysisPt *dcalc_ap,
                         int digits) override;
  string reportCheckDelay(const LibertyCell *cell,
                          const TimingArc *arc,
                          const Slew &from_slew,
                          const char *from_slew_annotation,
                          const Slew &to_slew,
                          float related_out_cap,
                          const Pvt *pvt,
                          const DcalcAnalysisPt *dcalc_ap,
                          int digits) override;
 void finishDrvrPin() override;

protected:
  // Find the liberty library to use for logic/slew thresholds.
  LibertyLibrary *thresholdLibrary(const Pin *load_pin);
  // Adjust load_delay and load_slew from driver thresholds to load thresholds.
  void thresholdAdjust(const Pin *load_pin,
		       ArcDelay &load_delay,
		       Slew &load_slew);

  Slew drvr_slew_;
  float multi_drvr_slew_factor_;
  const LibertyLibrary *drvr_library_;
  const RiseFall *drvr_rf_;
  // Parasitics returned by findParasitic that are reduced or estimated
  // that can be deleted after delay calculation for the driver pin
  // is finished.
  Vector<Parasitic*> unsaved_parasitics_;
  Vector<const Pin *> reduced_parasitic_drvrs_;
};

ArcDelayCalc *
makeLumpedCapDelayCalc(StaState *sta);

} // namespace
