

#include "NetworkCmp.hh"

#include <algorithm>

#include "StringUtil.hh"
#include "Liberty.hh"
#include "Network.hh"

namespace sta {

PortNameLess::PortNameLess(const Network *network) :
  network_(network)
{
}

bool
PortNameLess::operator()(const Port *port1,
			 const Port *port2) const
{
  return stringLess(network_->name(port1), network_->name(port2));
}

PinPathNameLess::PinPathNameLess(const Network *network) :
  network_(network)
{
}

bool
PinPathNameLess::operator()(const Pin *pin1,
			    const Pin *pin2) const
{
  return network_->pathNameLess(pin1, pin2);
}

NetPathNameLess::NetPathNameLess(const Network *network) :
  network_(network)
{
}

bool
NetPathNameLess::operator()(const Net *net1,
			    const Net *net2) const
{
  return network_->pathNameLess(net1, net2);
}

InstancePathNameLess::InstancePathNameLess(const Network *network) :
  network_(network)
{
}

bool
InstancePathNameLess::operator()(const Instance *inst1,
				 const Instance *inst2) const
{
  return network_->pathNameLess(inst1, inst2);
}

////////////////////////////////////////////////////////////////

PinSeq
sortByPathName(const PinSet *set,
              const Network *network)
{
  PinSeq pins;
  for (const Pin *pin : *set)
    pins.push_back(pin);
  sort(pins, PinPathNameLess(network));
  return pins;
}

PortSeq
sortByName(const PortSet *set,
           const Network *network)
{
  PortSeq ports;
  for (const Port *port : *set)
    ports.push_back(port);
  sort(ports, PortNameLess(network));
  return ports;
}

InstanceSeq
sortByPathName(InstanceSet *set,
              const Network *network)
{
  InstanceSeq insts;
  for (const Instance *inst : *set)
    insts.push_back(inst);
  sort(insts, InstancePathNameLess(network));
  return insts;
}

NetSeq
sortByPathName(NetSet *set,
              const Network *network)
{
  NetSeq nets;
  for (const Net *net : *set)
    nets.push_back(net);
  sort(nets, NetPathNameLess(network));
  return nets;
}

} // namespace
