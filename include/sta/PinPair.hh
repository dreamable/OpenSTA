



#include "Hash.hh"
#include "Set.hh"
#include "NetworkClass.hh"

namespace sta {

typedef std::pair<const Pin*, const Pin*> PinPair;

class PinPairLess
{
public:
  PinPairLess(const Network *network);
  bool operator()(const PinPair &pair1,
		  const PinPair &pair2) const;

private:
  const Network *network_;
};


class PinPairSet : public Set<PinPair, PinPairLess>
{
public:
  PinPairSet(const Network *network);
};

class PinPairHash
{
public:
  PinPairHash(const Network *network);
  size_t operator()(const PinPair &pair) const;

private:
  const Network *network_;
};

class PinPairEqual
{
public:
  bool operator()(const PinPair &pair1,
		  const PinPair &pair2) const;
};

} // namespace
