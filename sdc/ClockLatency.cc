

#include "ClockLatency.hh"

namespace sta {

ClockLatency::ClockLatency(const Clock *clk,
			   const Pin *pin) :
  clk_(clk),
  pin_(pin)
{
}

void
ClockLatency::setDelay(const RiseFallBoth *rf,
		       const MinMaxAll *min_max,
		       float delay)
{
  delays_.setValue(rf, min_max, delay);
}

float
ClockLatency::delay(const RiseFall *rf,
		    const MinMax *min_max)
{
  float latency;
  bool exists;
  delays_.value(rf, min_max, latency, exists);
  if (exists)
    return latency;
  else
    return 0.0;
}

void
ClockLatency::delay(const RiseFall *rf,
		    const MinMax *min_max,
		    // Return values.
		    float &latency,
		    bool &exists)

{
  delays_.value(rf, min_max, latency, exists);
  if (!exists)
    latency = 0.0;
}

void
ClockLatency::setDelay(const RiseFall *rf,
		       const MinMax *min_max,
		       float delay)
{
  delays_.setValue(rf, min_max, delay);
}

void
ClockLatency::setDelays(RiseFallMinMax *delays)
{
  delays_.setValues(delays);
}

RiseFallMinMax *
ClockLatency::delays()
{
  return &delays_;
}

} // namespace
