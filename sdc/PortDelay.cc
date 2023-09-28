

#include "PortDelay.hh"

#include "Sdc.hh"
#include "Network.hh"

namespace sta {

PortDelay::PortDelay(const Pin *pin,
		     const ClockEdge *clk_edge,
                     const Network *network) :
  pin_(pin),
  clk_edge_(clk_edge),
  source_latency_included_(false),
  network_latency_included_(false),
  ref_pin_(nullptr),
  delays_(),
  leaf_pins_(network)
{
}

Clock *
PortDelay::clock() const
{
  if (clk_edge_)
    return clk_edge_->clock();
  else
    return nullptr;
}

void
PortDelay::setRefPin(const Pin *ref_pin)
{
  ref_pin_ = ref_pin;
}

bool
PortDelay::sourceLatencyIncluded() const
{
  return source_latency_included_;
}

void
PortDelay::setSourceLatencyIncluded(bool included)
{
  source_latency_included_ = included;
}

bool
PortDelay::networkLatencyIncluded() const
{
  return network_latency_included_;
}

void
PortDelay::setNetworkLatencyIncluded(bool included)
{
  network_latency_included_ = included;
}

RiseFall *
PortDelay::refTransition() const
{
  // Reference pin transition is the clock transition.
  if (clk_edge_)
    return clk_edge_->transition();
  else
    return RiseFall::rise();
}

InputDelay::InputDelay(const Pin *pin,
		       const ClockEdge *clk_edge,
		       int index,
		       const Network *network) :
  PortDelay(pin, clk_edge, network),
  index_(index)
{
  findLeafLoadPins(pin, network, &leaf_pins_);
}

OutputDelay::OutputDelay(const Pin *pin,
			 const ClockEdge *clk_edge,
			 const Network *network) :
  PortDelay(pin, clk_edge, network)
{
  if (network)
    findLeafDriverPins(pin, network, &leaf_pins_);
}

////////////////////////////////////////////////////////////////

PortDelayLess::PortDelayLess(const Network *network) :
  network_(network)
{
}

bool
PortDelayLess::operator() (const PortDelay *delay1,
                           const PortDelay *delay2) const
{
  const Pin *pin1 = delay1->pin();
  const Pin *pin2 = delay2->pin();
  int pin_cmp = network_->pathNameCmp(pin1, pin2);
  if (pin_cmp < 0)
    return true;
  else if (pin_cmp > 0)
    return false;
  else
    return clkEdgeLess(delay1->clkEdge(), delay2->clkEdge());
}

} // namespace
