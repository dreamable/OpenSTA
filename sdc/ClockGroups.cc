

#include "ClockGroups.hh"

#include "StringUtil.hh"

namespace sta {

ClockGroups::ClockGroups(const char *name,
			 bool logically_exclusive,
			 bool physically_exclusive,
			 bool asynchronous,
			 bool allow_paths,
			 const char *comment) :
  SdcCmdComment(comment),
  name_(stringCopy(name)),
  logically_exclusive_(logically_exclusive),
  physically_exclusive_(physically_exclusive),
  asynchronous_(asynchronous),
  allow_paths_(allow_paths)
{
}

ClockGroups::~ClockGroups()
{
  stringDelete(name_);
  groups_.deleteContentsClear();
}

void
ClockGroups::makeClockGroup(ClockSet *clks)
{
  groups_.insert(clks);
}

void
ClockGroups::removeClock(Clock *clk)
{
  for (auto itr = groups_.cbegin(); itr != groups_.cend(); ) {
    ClockGroup *group = *itr;
    group->erase(clk);
    if (group->empty()) {
      itr = groups_.erase(itr);
      delete group;
    }
    else
      itr++;
  }
}

} // namespace
