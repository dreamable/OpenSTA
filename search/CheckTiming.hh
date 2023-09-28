



#include "Vector.hh"
#include "StringSeq.hh"
#include "NetworkClass.hh"
#include "GraphClass.hh"
#include "SdcClass.hh"
#include "StaState.hh"

namespace sta {

typedef StringSeq CheckError;
typedef Vector<CheckError*> CheckErrorSeq;

class CheckTiming : public StaState
{
public:
  explicit CheckTiming(StaState *sta);
  ~CheckTiming();
  CheckErrorSeq &check(bool no_input_delay,
		       bool no_output_delay,
		       bool reg_multiple_clks,
		       bool reg_no_clks,
		       bool unconstrained_endpoints,
		       bool loops,
		       bool generated_clks);

protected:
  void clear();
  void deleteErrors();
  void checkNoInputDelay();
  void checkNoOutputDelay();
  void checkRegClks(bool reg_multiple_clks,
		    bool reg_no_clks);
  void checkUnconstrainedEndpoints();
  bool hasClkedArrival(Vertex *vertex);
  void checkNoOutputDelay(PinSet &ends);
  void checkUnconstraintedOutputs(PinSet &unconstrained_ends);
  void checkUnconstrainedSetups(PinSet &unconstrained_ends);
  void checkLoops();
  bool hasClkedDepature(Pin *pin);
  bool hasClkedCheck(Vertex *vertex);
  bool hasMaxDelay(Pin *pin);
  void checkGeneratedClocks();
  void pushPinErrors(const char *msg,
		     PinSet &pins);
  void pushClkErrors(const char *msg,
		     ClockSet &clks);
  void errorMsgSubst(const char *msg,
		     int count,
		     string &error_msg);

  CheckErrorSeq errors_;
};

} // namespace
