



#include "LibertyClass.hh"
#include "NetworkClass.hh"
#include "SdcClass.hh"
#include "StaState.hh"

namespace sta {

InstanceSet
findRegInstances(ClockSet *clks, const RiseFallBoth *clk_rf,
		 bool edge_triggered, bool latches, StaState *sta);
PinSet
findRegDataPins(ClockSet *clks, const RiseFallBoth *clk_rf,
		bool edge_triggered, bool latches, StaState *sta);
PinSet
findRegClkPins(ClockSet *clks, const RiseFallBoth *clk_rf,
	       bool edge_triggered, bool latches, StaState *sta);
PinSet
findRegAsyncPins(ClockSet *clks, const RiseFallBoth *clk_rf,
		 bool edge_triggered, bool latches, StaState *sta);
PinSet
findRegOutputPins(ClockSet *clks, const RiseFallBoth *clk_rf,
		  bool edge_triggered, bool latches, StaState *sta);

void
initPathSenseThru();

} // namespace
