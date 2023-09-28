



#include "Zlib.hh"
#include "MinMax.hh"
#include "ParasiticsClass.hh"

namespace sta {

class Report;
class Network;
class Parasitics;
class ParasiticAnalysisPt;
class Instance;
class Corner;
class OperatingConditions;

// Read a file single value parasitics into analysis point ap.
// In a Spef file with triplet values the first value is used.
// Constraint min/max cnst_min_max and operating condition op_cond
// are used for parasitic network reduction.
// Return true if successful.
bool
readSpefFile(const char *filename,
	     Instance *instance,
	     ParasiticAnalysisPt *ap,
	     bool pin_cap_included,
	     bool keep_coupling_caps,
	     float coupling_cap_factor,
	     ReducedParasiticType reduce_to,
	     bool delete_after_reduce,
	     const OperatingConditions *op_cond,
	     const Corner *corner,
	     const MinMax *cnst_min_max,
	     bool quiet,
	     Report *report,
	     Network *network,
	     Parasitics *parasitics);

} // namespace
