



#include "NetworkClass.hh"
#include "SdcClass.hh"

namespace sta {

// Write SDC to a file.
// Allow SDC to apply to an instance to support write_context.
void
writeSdc(Instance *instance,
	 const char *filename,
	 const char *creator,
	 // Map hierarchical pins and instances to leaf pins and instances.
	 bool map_hpins,
	 // Replace non-sdc get functions with OpenSTA equivalents.
	 bool native,
	 int digits,
         bool gzip,
	 bool no_timestamp,
	 Sdc *sdc);

} // namespace
