

#include "ClockGatingCheck.hh"

namespace sta {

ClockGatingCheck::ClockGatingCheck() :
  active_value_(LogicValue::unknown)
{
}

void
ClockGatingCheck::setActiveValue(LogicValue value)
{
  active_value_ = value;
}

} // namespace
