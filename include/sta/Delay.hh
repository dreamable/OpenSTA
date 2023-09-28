



#include "StaConfig.hh"

#if (SSTA == 1)
  // Delays are Normal PDFs.
  #include "DelayNormal1.hh"
#elif (SSTA == 2)
  // Delays are Normal PDFs with early/late sigma.
  #include "DelayNormal2.hh"
#else
  // Delays are floats.
  #include "DelayFloat.hh"
#endif

namespace sta {

typedef Delay ArcDelay;
typedef Delay Slew;
typedef Delay Arrival;
typedef Delay Required;
typedef Delay Slack;

} // namespace
