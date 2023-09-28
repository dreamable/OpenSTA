



#include "SdcClass.hh"

namespace sta {

class Report;
class MinMax;
class Network;
class Graph;
class Corner;
class StaState;

// If unescaped_dividers is true, path names in the SDF do not have to
// escape hierarchy dividers when the path name is escaped.  For
// example, the escaped Verilog instance name "\inst1/inst2 " can be
// referenced as "inst1/inst2".  The correct SDF name is
// "inst1\/inst2", since the divider does not represent a change in
// hierarchy in this case.
//
// If incremental_only is true non-incremental annoatations are ignored.
//
// path is a hierararchial path prefix for instances and pins in the
// sdf file.  Pass 0 (nullptr) to specify no path.
//
// The cond_use option is used when the SDF file contains conditional
// delays and the library does not have conditional delay arcs.  If
// cond_use is min, the minimum of all conditional delays is used.  If
// cond_use is max, the maximum of all conditional delays is used.  If
// cond_use is min_max and min_max operating conditions are in use, the
// minimum of the conditional delay values is used for minimum operating
// conditions and the maximum of the conditional delay values is used for
// maximum operating conditions.

bool
readSdf(const char *filename,
        const char *path,
        Corner *corner,
        bool unescaped_dividers,
        bool incremental_only,
        MinMaxAll *cond_use,
        StaState *sta);

} // namespace
