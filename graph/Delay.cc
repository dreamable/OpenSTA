

#include "Machine.hh"
#include "StringUtil.hh"
#include "Units.hh"
#include "StaState.hh"
#include "Delay.hh"

namespace sta {

const char *
delayAsString(const Delay &delay,
	      const StaState *sta)
{
  return delayAsString(delay, sta, sta->units()->timeUnit()->digits());
}

} // namespace
