

#include "LinearModel.hh"

#include "Units.hh"
#include "Liberty.hh"

namespace sta {

GateLinearModel::GateLinearModel(float intrinsic,
				 float resistance) :
  intrinsic_(intrinsic),
  resistance_(resistance)
{
}

void
GateLinearModel::gateDelay(const LibertyCell *,
			   const Pvt *,
			   float,
			   float load_cap,
			   float,
			   bool,
			   // return values
			   ArcDelay &gate_delay,
			   Slew &drvr_slew) const
{
  gate_delay = intrinsic_ + resistance_ * load_cap;
  drvr_slew = 0.0;
}

string
GateLinearModel::reportGateDelay(const LibertyCell *cell,
				 const Pvt *,
				 float,
				 float load_cap,
				 float,
				 bool,
				 int digits) const
{
  const LibertyLibrary *library = cell->libertyLibrary();
  const Units *units = library->units();
  const Unit *time_unit = units->timeUnit();
  const Unit *res_unit = units->resistanceUnit();
  const Unit *cap_unit = units->capacitanceUnit();
  string result = "Delay = ";
  result += time_unit->asString(intrinsic_, digits);
  result += " + ";
  result += res_unit->asString(resistance_, digits);
  result += " * ";
  result += cap_unit->asString(load_cap, digits);
  result += " = ";
  float delay = intrinsic_ + resistance_ * load_cap;
  result += time_unit->asString(delay, digits);
  return result;
}

float
GateLinearModel::driveResistance(const LibertyCell *,
				 const Pvt *) const
{
  return resistance_;
}

void
GateLinearModel::setIsScaled(bool)
{
}

CheckLinearModel::CheckLinearModel(float intrinsic) :
  intrinsic_(intrinsic)
{
}

void
CheckLinearModel::checkDelay(const LibertyCell *,
			     const Pvt *,
			     float,
			     float,
			     float,
			     bool,
			     ArcDelay &margin) const
{
  margin = intrinsic_;
}

string
CheckLinearModel::reportCheckDelay(const LibertyCell *cell,
				   const Pvt *,
				   float,
				   const char *,
				   float,
				   float,
				   bool,
				   int digits) const
{
  const LibertyLibrary *library = cell->libertyLibrary();
  const Units *units = library->units();
  const Unit *time_unit = units->timeUnit();
  string result = "Check = ";
  result += time_unit->asString(intrinsic_, digits);
  return result;
}

void
CheckLinearModel::setIsScaled(bool)
{
}

} // namespace
