



#include "StringSeq.hh"

namespace sta {

class ArcDelayCalc;
class StaState;

typedef ArcDelayCalc *(*MakeArcDelayCalc)(StaState *sta);

// Register builtin delay calculators.
void
registerDelayCalcs();
// Register a delay calculator for the set_delay_calc command.
void
registerDelayCalc(const char *name,
		  MakeArcDelayCalc maker);
bool
isDelayCalcName(const char *name);
StringSeq
delayCalcNames();
void
deleteDelayCalcs();

// Make a registered delay calculator by name.
ArcDelayCalc *
makeDelayCalc(const char *name,
	      StaState *sta);

} // namespace
