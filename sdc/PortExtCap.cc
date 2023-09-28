

#include "PortExtCap.hh"

namespace sta {

PortExtCap::PortExtCap(const Port *port) :
  port_(port)
{
}

void
PortExtCap::pinCap(const RiseFall *rf,
		   const MinMax *min_max,
		   // Return values.
		   float &cap,
		   bool &exists)
{
  pin_cap_.value(rf, min_max, cap, exists);
}

void
PortExtCap::setPinCap(float cap,
		      const RiseFall *rf,
		      const MinMax *min_max)
{
  pin_cap_.setValue(rf, min_max, cap);
}

void
PortExtCap::wireCap(const RiseFall *rf,
		    const MinMax *min_max,
		    // Return values.
		    float &cap,
		    bool &exists)
{
  wire_cap_.value(rf, min_max, cap, exists);
}

void
PortExtCap::setWireCap(float cap,
		       const RiseFall *rf,
		       const MinMax *min_max)
{
  wire_cap_.setValue(rf, min_max, cap);
}

void
PortExtCap::setFanout(int fanout,
		      const MinMax *min_max)
{
  fanout_.setValue(min_max, fanout);
}


void
PortExtCap::fanout(const MinMax *min_max,
		   // Return values.
		   int &fanout,
		   bool &exists)
{
  fanout_.value(min_max, fanout, exists);
}

} // namespace
