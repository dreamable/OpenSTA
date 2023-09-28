

#include "UnitDelayCalc.hh"

#include "Units.hh"

namespace sta {

ArcDelayCalc *
makeUnitDelayCalc(StaState *sta)
{
  return new UnitDelayCalc(sta);
}

UnitDelayCalc::UnitDelayCalc(StaState *sta) :
  ArcDelayCalc(sta)
{
}

ArcDelayCalc *
UnitDelayCalc::copy()
{
  return new UnitDelayCalc(this);
}

Parasitic *
UnitDelayCalc::findParasitic(const Pin *,
			     const RiseFall *,
			     const DcalcAnalysisPt *)
{
  return nullptr;
}

ReducedParasiticType
UnitDelayCalc::reducedParasiticType() const
{
  return ReducedParasiticType::none;
}

void
UnitDelayCalc::inputPortDelay(const Pin *,
			      float,
			      const RiseFall *,
			      const Parasitic *,
			      const DcalcAnalysisPt *)
{
}

void
UnitDelayCalc::gateDelay(const LibertyCell *,
			 const TimingArc *,
			 const Slew &,
			 float,
			 const Parasitic *,
			 float,
			 const Pvt *, const DcalcAnalysisPt *,
			 // Return values.
			 ArcDelay &gate_delay, Slew &drvr_slew)
{
  gate_delay = units_->timeUnit()->scale();
  drvr_slew = 0.0;
}

void
UnitDelayCalc::loadDelay(const Pin *,
			 ArcDelay &wire_delay,
			 Slew &load_slew)
{
  wire_delay = 0.0;
  load_slew = 0.0;
}

float
UnitDelayCalc::ceff(const LibertyCell *,
		    const TimingArc *,
		    const Slew &,
		    float,
		    const Parasitic *,
		    float,
		    const Pvt *,
		    const DcalcAnalysisPt *)
{
  return 0.0;
}

string
UnitDelayCalc::reportGateDelay(const LibertyCell *,
			       const TimingArc *,
			       const Slew &,
			       float,
			       const Parasitic *,
			       float,
			       const Pvt *,
			       const DcalcAnalysisPt *,
			       int)
{
  string result("Delay = 1.0\n");
  result += "Slew = 0.0\n";
  return result;
}

void
UnitDelayCalc::checkDelay(const LibertyCell *,
			  const TimingArc *,
			  const Slew &,
			  const Slew &,
			  float,
			  const Pvt *,
			  const DcalcAnalysisPt *,
			  // Return values.
			  ArcDelay &margin)
{
  margin = units_->timeUnit()->scale();
}

string
UnitDelayCalc::reportCheckDelay(const LibertyCell *,
				const TimingArc *,
				const Slew &,
				const char *,
				const Slew &,
				float,
				const Pvt *,
				const DcalcAnalysisPt *,
				int)
{
  return "Check = 1.0\n";
}

void
UnitDelayCalc::finishDrvrPin()
{
}

} // namespace
