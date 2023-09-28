



#include "SdcClass.hh"
#include "RiseFallMinMax.hh"

namespace sta {

class ClockGatingCheck
{
public:
  ClockGatingCheck();
  RiseFallMinMax *margins() { return &margins_; }
  void setActiveValue(LogicValue value);
  LogicValue activeValue() const { return active_value_; }

private:
  RiseFallMinMax margins_;
  LogicValue active_value_;
};

} // namespace
