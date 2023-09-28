



#include "NetworkClass.hh"
#include "SdcClass.hh"

namespace sta {

class Corner;
class Parasitic;
class ParasiticAnalysisPt;
class StaState;

// Reduce parasitic network to pi elmore model for drvr_pin.
void
reduceToPiElmore(Parasitic *parasitic_network,
		 const Pin *drvr_pin,
		 float coupling_cap_factor,
		 const OperatingConditions *op_cond,
		 const Corner *corner,
		 const MinMax *cnst_min_max,
		 const ParasiticAnalysisPt *ap,
		 StaState *sta);

// Reduce parasitic network to pi and 2nd order pole/residue models
// for drvr_pin.
void
reduceToPiPoleResidue2(Parasitic *parasitic_network,
		       const Pin *drvr_pin,
		       float coupling_cap_factor,
		       const OperatingConditions *op_cond,
		       const Corner *corner,
		       const MinMax *cnst_min_max,
		       const ParasiticAnalysisPt *ap,
		       StaState *sta);

} // namespace
