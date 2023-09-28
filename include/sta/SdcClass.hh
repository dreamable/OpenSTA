



#include "Map.hh"
#include "Set.hh"
#include "Vector.hh"
#include "LibertyClass.hh"
#include "NetworkClass.hh"
#include "MinMaxValues.hh"
#include "PinPair.hh"

namespace sta {

class Sdc;
class Clock;
class ClockEdge;
class CycleAccting;
class InputDelay;
class OutputDelay;
class FalsePath;
class PathDelay;
class MultiCyclePath;
class FilterPath;
class GroupPath;
class ExceptionFromTo;
class ExceptionFrom;
class ExceptionThru;
class ExceptionTo;
class ExceptionPt;
class InputDrive;
class MinMax;
class MinMaxAll;
class RiseFallMinMax;
class DisabledInstancePorts;
class DisabledCellPorts;
class ExceptionPath;
class DataCheck;
class Wireload;
class ClockLatency;
class ClockInsertion;
class ClockGroups;
class PortDelay;

enum class AnalysisType { single, bc_wc, ocv };

enum class ExceptionPathType { false_path, loop, multi_cycle, path_delay,
			       group_path, filter, any};

enum class ClockSense { positive, negative, stop };

typedef std::pair<const Clock*, const Clock*> ClockPair;

class ClockIndexLess
{
public:
  bool operator()(const Clock *clk1,
                  const Clock *clk2) const;
};

typedef Vector<float> FloatSeq;
typedef Vector<int> IntSeq;
typedef Vector<Clock*> ClockSeq;
typedef Set<Clock*, ClockIndexLess> ClockSet;
typedef ClockSet ClockGroup;
typedef Vector<PinSet*> PinSetSeq;
typedef MinMax SetupHold;
typedef MinMaxAll SetupHoldAll;
typedef Vector<ExceptionThru*> ExceptionThruSeq;
typedef Set<LibertyPortPair, LibertyPortPairLess> LibertyPortPairSet;
typedef Map<const Instance*, DisabledInstancePorts*> DisabledInstancePortsMap;
typedef Map<const LibertyCell*, DisabledCellPorts*> DisabledCellPortsMap;
typedef MinMaxValues<float> ClockUncertainties;
typedef Set<ExceptionPath*> ExceptionPathSet;
typedef PinPair EdgePins;
typedef PinPairSet EdgePinsSet;
typedef Map<const Pin*, LogicValue> LogicValueMap;

class ClockSetLess
{
public:
  bool operator()(const ClockSet *set1,
                  const ClockSet *set2) const;
};

typedef Set<ClockGroup*, ClockSetLess> ClockGroupSet;

// For Search.
class ExceptionState;

class ExceptionStateLess
{
public:
  ExceptionStateLess(const Network *network);
  bool operator()(const ExceptionState *state1,
                  const ExceptionState *state2) const;

private:
  const Network *network_;
};

class ExceptionPath;
typedef Set<ExceptionState*, ExceptionStateLess> ExceptionStateSet;

enum class CrprMode { same_pin, same_transition };

// Constraint applies to clock or data paths.
enum class PathClkOrData { clk, data };

const int path_clk_or_data_count = 2;

enum class TimingDerateType { cell_delay, cell_check, net_delay };
constexpr int timing_derate_type_count = 3;
enum class TimingDerateCellType { cell_delay, cell_check };
constexpr int timing_derate_cell_type_count = 2;

} // namespace
