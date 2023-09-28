



#include "LumpedCapDelayCalc.hh"

namespace sta {

// Base class for delay calculators with RC wire delay.
class RCDelayCalc : public LumpedCapDelayCalc
{
public:
  RCDelayCalc(StaState *sta);
  ArcDelayCalc *copy() override;
  void inputPortDelay(const Pin *port_pin,
                      float in_slew,
                      const RiseFall *rf,
                      const Parasitic *parasitic,
                      const DcalcAnalysisPt *dcalc_ap) override;

protected:
  // Helper function for input ports driving dspf parasitic.
  void dspfWireDelaySlew(const Pin *load_pin,
			 float elmore,
			 ArcDelay &wire_delay,
			 Slew &load_slew);

  const LibertyCell *drvr_cell_;
  const Parasitic *drvr_parasitic_;
  bool input_port_;
};

} // namespace
