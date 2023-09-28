

#include "Delay.hh"

#include "StaConfig.hh"
#include "Fuzzy.hh"
#include "Units.hh"
#include "StaState.hh"

// Non-SSTA compilation.
#if !SSTA

namespace sta {

static Delay delay_init_values[MinMax::index_count];

void
initDelayConstants()
{
  delay_init_values[MinMax::minIndex()] = MinMax::min()->initValue();
  delay_init_values[MinMax::maxIndex()] = MinMax::max()->initValue();
}

const char *
delayAsString(const Delay &delay,
	      const StaState *sta)
{
  return delayAsString(delay, sta, sta->units()->timeUnit()->digits());
}

const char *
delayAsString(const Delay &delay,
	      const StaState *sta,
	      int digits)
{
  return sta->units()->timeUnit()->asString(delay, digits);
}

const char *
delayAsString(const Delay &delay,
	      const EarlyLate *,
	      const StaState *sta,
	      int digits)
{
  const Unit *unit = sta->units()->timeUnit();
  return unit->asString(delay, digits);
}

const Delay &
delayInitValue(const MinMax *min_max)
{
  return delay_init_values[min_max->index()];
}

bool
delayIsInitValue(const Delay &delay,
		 const MinMax *min_max)
{
  return fuzzyEqual(delay, min_max->initValue());
}

bool
delayZero(const Delay &delay)
{
  return fuzzyZero(delay);
}

bool
delayInf(const Delay &delay)
{
  return fuzzyInf(delay);
}

bool
delayEqual(const Delay &delay1,
	   const Delay &delay2)
{
  return fuzzyEqual(delay1, delay2);
}

bool
delayLess(const Delay &delay1,
	  const Delay &delay2,
	  const StaState *)
{
  return fuzzyLess(delay1, delay2);
}

bool
delayLess(const Delay &delay1,
	  const Delay &delay2,
	  const MinMax *min_max,
	  const StaState *)
{
  if (min_max == MinMax::max())
    return fuzzyLess(delay1, delay2);
  else
    return fuzzyGreater(delay1, delay2);
}

bool
delayLessEqual(const Delay &delay1,
	       const Delay &delay2,
	       const StaState *)
{
  return fuzzyLessEqual(delay1, delay2);
}

bool
delayLessEqual(const Delay &delay1,
	       const Delay &delay2,
	       const MinMax *min_max,
	       const StaState *)
{
  if (min_max == MinMax::max())
    return fuzzyLessEqual(delay1, delay2);
  else
    return fuzzyGreaterEqual(delay1, delay2);
}

bool
delayGreater(const Delay &delay1,
	     const Delay &delay2,
	     const StaState *)
{
  return fuzzyGreater(delay1, delay2);
}

bool
delayGreater(const Delay &delay1,
	     const Delay &delay2,
	     const MinMax *min_max,
	     const StaState *)
{
  if (min_max == MinMax::max())
    return fuzzyGreater(delay1, delay2);
  else
    return fuzzyLess(delay1, delay2);
}

bool
delayGreaterEqual(const Delay &delay1,
		  const Delay &delay2,
		  const StaState *)
{
  return fuzzyGreaterEqual(delay1, delay2);
}

bool
delayGreaterEqual(const Delay &delay1,
		  const Delay &delay2,
		  const MinMax *min_max,
		  const StaState *)
{
  if (min_max == MinMax::max())
    return fuzzyGreaterEqual(delay1, delay2);
  else
    return fuzzyLessEqual(delay1, delay2);
}

Delay
delayRemove(const Delay &delay1,
	    const Delay &delay2)
{
  return delay1 - delay2;
}

float
delayRatio(const Delay &delay1,
	   const Delay &delay2)
{
  return delay1 / delay2;
}

} // namespace

#endif // !SSTA
