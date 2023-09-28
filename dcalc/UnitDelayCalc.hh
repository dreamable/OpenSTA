



#include "ArcDelayCalc.hh"

namespace sta {

// Unit delay calculator.
class UnitDelayCalc : public ArcDelayCalc
{
public:
  UnitDelayCalc(StaState *sta);
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
  void loadDelay(const Pin *load_pin,
                 // Return values.
                 ArcDelay &wire_delay,
                 Slew &load_slew) override;
  void setMultiDrvrSlewFactor(float) override {}
  float ceff(const LibertyCell *drvr_cell,
             const TimingArc *arc,
             const Slew &in_slew,
             float load_cap,
             const Parasitic *drvr_parasitic,
             float related_out_cap,
             const Pvt *pvt,
             const DcalcAnalysisPt *dcalc_ap) override;
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
};

ArcDelayCalc *
makeUnitDelayCalc(StaState *sta);

} // namespace
