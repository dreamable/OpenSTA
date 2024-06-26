
#include "RCDelayCalc.hh"

#include "Liberty.hh"
#include "Network.hh"
#include "Sdc.hh"
#include "Parasitics.hh"
#include "GraphDelayCalc.hh"

namespace sta
{

  RCDelayCalc::RCDelayCalc(StaState *sta) : LumpedCapDelayCalc(sta)
  {
  }

  ArcDelayCalc *
  RCDelayCalc::copy()
  {
    return new RCDelayCalc(this);
  }

  void
  RCDelayCalc::inputPortDelay(const Pin *,
                              float in_slew,
                              const RiseFall *rf,
                              const Parasitic *parasitic,
                              const DcalcAnalysisPt *)
  {
    drvr_parasitic_ = parasitic;
    drvr_slew_ = in_slew;
    drvr_rf_ = rf;
    drvr_cell_ = nullptr;
    drvr_library_ = network_->defaultLibertyLibrary();
    multi_drvr_slew_factor_ = 1.0F;
    input_port_ = true;
  }

  // For DSPF on an input port the elmore delay is used as the time
  // constant of an exponential waveform.  The delay to the logic
  // threshold and slew are computed for the exponential waveform.
  // Note that this uses the driver thresholds and relies on
  // thresholdAdjust to convert the delay and slew to the load's thresholds.
  void
  RCDelayCalc::dspfWireDelaySlew(const Pin *,
                                 float elmore,
                                 ArcDelay &wire_delay,
                                 Slew &load_slew)
  {
    float vth = drvr_library_->inputThreshold(drvr_rf_);
    float vl = drvr_library_->slewLowerThreshold(drvr_rf_);
    float vh = drvr_library_->slewUpperThreshold(drvr_rf_);
    float slew_derate = drvr_library_->slewDerateFromLibrary();
    wire_delay = static_cast<float>(-elmore * log(1.0 - vth));
    load_slew = (drvr_slew_ + elmore * log((1.0 - vl) / (1.0 - vh)) / slew_derate) * multi_drvr_slew_factor_;
  }

} // namespace
