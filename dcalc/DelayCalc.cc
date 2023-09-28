

#include "DelayCalc.hh"

#include "Map.hh"
#include "StringUtil.hh"
#include "UnitDelayCalc.hh"
#include "LumpedCapDelayCalc.hh"
#include "SlewDegradeDelayCalc.hh"
#include "DmpDelayCalc.hh"
#include "ArnoldiDelayCalc.hh"

namespace sta {

typedef Map<const char*, MakeArcDelayCalc, CharPtrLess> DelayCalcMap;

static DelayCalcMap *delay_calcs = nullptr;

void
registerDelayCalcs()
{
  registerDelayCalc("unit", makeUnitDelayCalc);
  registerDelayCalc("lumped_cap", makeLumpedCapDelayCalc);
  registerDelayCalc("slew_degrade", makeSlewDegradeDelayCalc);
  registerDelayCalc("dmp_ceff_elmore", makeDmpCeffElmoreDelayCalc);
  registerDelayCalc("dmp_ceff_two_pole", makeDmpCeffTwoPoleDelayCalc);
  registerDelayCalc("arnoldi", makeArnoldiDelayCalc);
}

void
registerDelayCalc(const char *name,
		  MakeArcDelayCalc maker)
{
  if (delay_calcs == nullptr)
    delay_calcs = new DelayCalcMap;
  (*delay_calcs)[name] = maker;
}

void
deleteDelayCalcs()
{
  delete delay_calcs;
  delay_calcs = nullptr;
}

ArcDelayCalc *
makeDelayCalc(const char *name,
	      StaState *sta)
{
  MakeArcDelayCalc maker = delay_calcs->findKey(name);
  if (maker)
    return maker(sta);
  else
    return nullptr;
}

bool
isDelayCalcName(const char *name)
{
  return delay_calcs->hasKey(name);
}

StringSeq
delayCalcNames()
{
  StringSeq names;
  for (auto name_dcalc : *delay_calcs) {
    const char *name = name_dcalc.first;
    names.push_back(name);
  }
  return names;
}

} // namespace
