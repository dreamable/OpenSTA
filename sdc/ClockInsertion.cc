

#include "ClockInsertion.hh"

namespace sta {

ClockInsertion::ClockInsertion(const Clock *clk,
			       const Pin *pin) :
  clk_(clk),
  pin_(pin)
{
}

void
ClockInsertion::setDelay(const RiseFallBoth *rf,
			 const MinMaxAll *min_max,
			 const EarlyLateAll *early_late,
			 float delay)
{
  for (auto el_index : early_late->rangeIndex())
    delays_[el_index].setValue(rf, min_max, delay);
}

float
ClockInsertion::delay(const RiseFall *rf,
		      const MinMax *min_max,
		      const EarlyLate *early_late)
{
  float insertion;
  bool exists;
  delays_[early_late->index()].value(rf, min_max, insertion, exists);
  if (exists)
    return insertion;
  else
    return 0.0;
}

void
ClockInsertion::delay(const RiseFall *rf,
		      const MinMax *min_max,
		      const EarlyLate *early_late,
		      // Return values.
		      float &insertion,
		      bool &exists)

{
  delays_[early_late->index()].value(rf, min_max, insertion, exists);
  if (!exists)
    insertion = 0.0;
}

void
ClockInsertion::setDelay(const RiseFall *rf,
			 const MinMax *min_max,
			 const EarlyLate *early_late,
			 float delay)
{
  delays_[early_late->index()].setValue(rf, min_max, delay);
}

void
ClockInsertion::setDelays(RiseFallMinMax *delays)
{
  for (auto el_index : EarlyLate::rangeIndex())
    delays_[el_index].setValues(delays);
}

RiseFallMinMax *
ClockInsertion::delays(const EarlyLate *early_late)
{
  return &delays_[early_late->index()];
}

} // namespace
