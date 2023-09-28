

#include "NetCaps.hh"

namespace sta {

NetCaps::NetCaps()
{
}

NetCaps::NetCaps(float pin_cap,
		 float wire_cap,
		 float fanout,
		 bool has_set_load) :
  pin_cap_(pin_cap),
  wire_cap_(wire_cap),
  fanout_(fanout),
  has_set_load_(has_set_load)
{
}

void
NetCaps::init(float pin_cap,
	      float wire_cap,
	      float fanout,
	      bool has_set_load)
{
  pin_cap_ = pin_cap;
  wire_cap_ = wire_cap;
  fanout_ = fanout;
  has_set_load_ = has_set_load;
}

} // namespace
