



#include "LibertyClass.hh"
#include "NetworkClass.hh"

namespace sta {

// Comparison operators for network objects.

class PortNameLess
{
public:
  explicit PortNameLess(const Network *network);
  bool operator()(const Port *port1,
		  const Port *port2) const;

private:
  const Network *network_;
};

class PinPathNameLess
{
public:
  explicit PinPathNameLess(const Network *network);
  bool operator()(const Pin *pin1,
		  const Pin *pin2) const;

private:
  const Network *network_;
};

class InstancePathNameLess
{
public:
  explicit InstancePathNameLess(const Network *network);
  bool operator()(const Instance *inst1,
		  const Instance *inst2) const;

private:
  const Network *network_;
};

class NetPathNameLess
{
public:
  explicit NetPathNameLess(const Network *network);
  bool operator()(const Net *net1,
		  const Net *net2) const;

private:
  const Network *network_;
};

PinSeq
sortByPathName(const PinSet *set,
               const Network *network);
PortSeq
sortByName(const PortSet *set,
           const Network *network);
InstanceSeq
sortByPathName(InstanceSet *set,
               const Network *network);
NetSeq
sortByPathName(NetSet *set,
               const Network *network);

} // namespace
