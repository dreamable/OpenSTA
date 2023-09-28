



#include "Map.hh"
#include "NetworkClass.hh"
#include "LibertyClass.hh"
#include "SdcClass.hh"

namespace sta {

class TimingRole;
class DisabledCellPorts;
class DisabledInstancePorts;

typedef Vector<DisabledInstancePorts*> DisabledInstancePortsSeq;
typedef Vector<DisabledCellPorts*> DisabledCellPortsSeq;
typedef Vector<LibertyPortPair> LibertyPortPairSeq;
typedef Set<TimingArcSet*> TimingArcSetSet;

// Base class for disabled cell and instance ports.
class DisabledPorts
{
public:
  DisabledPorts();
  ~DisabledPorts();
  void setDisabledAll();
  void removeDisabledAll();
  void setDisabledFrom(LibertyPort *port);
  void removeDisabledFrom(LibertyPort *port);
  void setDisabledTo(LibertyPort *port);
  void removeDisabledTo(LibertyPort *port);
  void setDisabledFromTo(LibertyPort *from,
                         LibertyPort *to);
  void removeDisabledFromTo(LibertyPort *from,
                            LibertyPort *to);
  bool isDisabled(LibertyPort *from,
                  LibertyPort *to,
                  const TimingRole *role);
  LibertyPortPairSet *fromTo() const { return from_to_; }
  LibertyPortSet *from() const { return from_; }
  LibertyPortSet *to() const { return to_; }
  bool all() const { return all_; }

private:
  bool all_;
  LibertyPortSet *from_;
  LibertyPortSet *to_;
  LibertyPortPairSet *from_to_;
};

// set_disable_timing cell [-from] [-to]
class DisabledCellPorts : public DisabledPorts
{
public:
  DisabledCellPorts(LibertyCell *cell);
  ~DisabledCellPorts();
  LibertyCell *cell() const { return cell_; }
  void setDisabled(TimingArcSet *arc_set);
  void removeDisabled(TimingArcSet *arc_set);
  bool isDisabled(TimingArcSet *arc_set) const;
  TimingArcSetSet *timingArcSets() const { return arc_sets_; }

  using DisabledPorts::isDisabled;

private:
  LibertyCell *cell_;
  TimingArcSetSet *arc_sets_;
};

// set_disable_timing instance [-from] [-to]
class DisabledInstancePorts : public DisabledPorts
{
public:
  DisabledInstancePorts(Instance *inst);
  Instance *instance() const { return inst_; }

private:
  Instance *inst_;
};

DisabledCellPortsSeq
sortByName(DisabledCellPortsMap *cell_map);
DisabledInstancePortsSeq
sortByPathName(const DisabledInstancePortsMap *inst_map,
               const Network *network);
LibertyPortPairSeq
sortByName(const LibertyPortPairSet *set);

} // namespace
