



#include "MinMax.hh"
#include "Transition.hh"
#include "RiseFallMinMax.hh"
#include "MinMaxValues.hh"
#include "NetworkClass.hh"

namespace sta {

typedef MinMaxIntValues FanoutValues;

// Port external pin and wire capacitance (set_load -pin_load -wire_load).
class PortExtCap
{
public:
  PortExtCap(const Port *port);
  const Port *port() { return port_; }
  void pinCap(const RiseFall *rf,
	      const MinMax *min_max,
	      // Return values.
	      float &cap,
              bool &exists);
  RiseFallMinMax *pinCap() { return &pin_cap_; }
  void setPinCap(float cap,
		 const RiseFall *rf,
		 const MinMax *min_max);
  void wireCap(const RiseFall *rf,
	       const MinMax *min_max,
	       // Return values.
	       float &cap,
               bool &exists);
  RiseFallMinMax *wireCap() { return &wire_cap_; }
  void setWireCap(float cap,
		  const RiseFall *rf,
		  const MinMax *min_max);
  void setFanout(int fanout,
		 const MinMax *min_max);
  void fanout(const MinMax *min_max,
	      // Return values.
	      int &fanout,
	      bool &exists);
  FanoutValues *fanout() { return &fanout_; }

private:
  const Port *port_;
  RiseFallMinMax pin_cap_;
  RiseFallMinMax wire_cap_;
  FanoutValues fanout_;
};

} // namespace
