



#include <cstdint>

#include "Set.hh"
#include "Vector.hh"
#include "Iterator.hh"

namespace sta {

class Network;
class NetworkEdit;
class NetworkReader;
class Library;
class Cell;
class Port;
class PortDirection;
class Instance;
class Pin;
class Term;
class Net;
class ConstantPinIterator;
class ViewType;
class LibertyLibrary;

typedef Iterator<Library*> LibraryIterator;
typedef Iterator<LibertyLibrary*> LibertyLibraryIterator;
typedef Vector<Cell*> CellSeq;
typedef Vector<const Port*> PortSeq;
typedef Iterator<Port*> CellPortIterator;
typedef Iterator<Port*> CellPortBitIterator;
typedef Iterator<Port*> PortMemberIterator;

typedef Vector<const Pin*> PinSeq;
typedef Vector<const Instance*> InstanceSeq;
typedef Vector<const Net*> NetSeq;
typedef Iterator<Instance*> InstanceChildIterator;
typedef Iterator<Pin*> InstancePinIterator;
typedef Iterator<Net*> InstanceNetIterator;
typedef Iterator<Instance*> LeafInstanceIterator;
typedef Iterator<Net*> NetIterator;
typedef Iterator<const Pin*> NetPinIterator;
typedef Iterator<Term*> NetTermIterator;
typedef Iterator<const Pin*> ConnectedPinIterator;
typedef ConnectedPinIterator NetConnectedPinIterator;
typedef ConnectedPinIterator PinConnectedPinIterator;
typedef uint32_t ObjectId;

enum class LogicValue : unsigned { zero, one, unknown, rise, fall };

class CellIdLess
{
public:
  CellIdLess(const Network *network);
  bool operator()(const Cell *cell1,
                  const Cell *cell2) const;
private:
  const Network *network_;
};

class PortIdLess
{
public:
  PortIdLess(const Network *network);
  bool operator()(const Port *port1,
                  const Port *port2) const;
private:
  const Network *network_;
};

class InstanceIdLess
{
public:
  InstanceIdLess(const Network *network);
  bool operator()(const Instance *inst1,
                  const Instance *inst2) const;
private:
  const Network *network_;
};

class PinIdLess
{
public:
  PinIdLess(const Network *network);
  bool operator()(const Pin *pin1,
                  const Pin *pin2) const;
private:
  const Network *network_;
};

class PinIdHash
{
public:
  PinIdHash(const Network *network);
  size_t operator()(const Pin *pin) const;

private:
  const Network *network_;
};

class NetIdLess
{
public:
  NetIdLess(const Network *network);
  bool operator()(const Net *net1,
                  const Net *net2) const;
private:
  const Network *network_;
};

////////////////////////////////////////////////////////////////

class CellSet : public Set<const Cell*, CellIdLess>
{
public:
  CellSet(const Network *network);
};

class PortSet : public Set<const Port*, PortIdLess>
{
public:
  PortSet(const Network *network);
};

class InstanceSet : public Set<const Instance*, InstanceIdLess>
{
public:
  InstanceSet();
  InstanceSet(const Network *network);
  static int compare(const InstanceSet *set1,
                     const InstanceSet *set2,
                     const Network *network);
  static bool intersects(const InstanceSet *set1,
                         const InstanceSet *set2,
                         const Network *network);
};

class PinSet : public Set<const Pin*, PinIdLess>
{
public:
  PinSet();
  PinSet(const Network *network);
  static int compare(const PinSet *set1,
                     const PinSet *set2,
                     const Network *network);
  static bool intersects(const PinSet *set1,
                         const PinSet *set2,
                         const Network *network);
};

class NetSet : public Set<const Net*, NetIdLess>
{
public:
  NetSet();
  NetSet(const Network *network);
  static int compare(const NetSet *set1,
                     const NetSet *set2,
                     const Network *network);
  static bool intersects(const NetSet *set1,
                         const NetSet *set2,
                         const Network *network);
};

} // namespace
