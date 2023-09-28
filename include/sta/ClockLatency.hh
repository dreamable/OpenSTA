



#include "MinMax.hh"
#include "NetworkClass.hh"
#include "Transition.hh"
#include "SdcClass.hh"
#include "RiseFallMinMax.hh"

namespace sta {

class ClockLatency
{
public:
  ClockLatency(const Clock *clk,
	       const Pin *pin);
  const Clock *clock() const { return clk_; }
  const Pin *pin() const { return pin_; }
  float delay(const RiseFall *rf,
	      const MinMax *min_max);
  void delay(const RiseFall *rf,
	     const MinMax *min_max,
	     // Return values.
	     float &latency,
	     bool &exists);
  RiseFallMinMax *delays();
  void setDelay(const RiseFall *rf,
		const MinMax *min_max,
		float delay);
  void setDelay(const RiseFallBoth *rf,
		const MinMaxAll *min_max,
		float delay);
  void setDelays(RiseFallMinMax *delays);

private:
  const Clock *clk_;
  const Pin *pin_;
  RiseFallMinMax delays_;
};

} // namespace
