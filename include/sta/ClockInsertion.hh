



#include "MinMax.hh"
#include "NetworkClass.hh"
#include "SdcClass.hh"
#include "RiseFallMinMax.hh"
#include "Transition.hh"

namespace sta {

class ClockInsertion
{
public:
  ClockInsertion(const Clock *clk, const Pin *pin);
  const Clock *clock() const { return clk_; }
  const Pin *pin() const { return pin_; }
  float delay(const RiseFall *rf, const MinMax *min_max,
	      const EarlyLate *early_late);
  void delay(const RiseFall *rf, const MinMax *min_max,
	     const EarlyLate *early_late,
	     // Return values.
	     float &insertion, bool &exists);
  RiseFallMinMax *delays(const EarlyLate *early_late);
  void setDelay(const RiseFall *rf, const MinMax *min_max,
		const EarlyLate *early_late, float delay);
  void setDelay(const RiseFallBoth *rf, const MinMaxAll *min_max,
		const EarlyLateAll *early_late, float delay);
  void setDelays(RiseFallMinMax *delays);

private:
  const Clock *clk_;
  const Pin *pin_;
  RiseFallMinMax delays_[EarlyLate::index_count];
};

} // namespace
