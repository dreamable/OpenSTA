



#include "SdcCmdComment.hh"
#include "SdcClass.hh"

namespace sta {

class ClockGroups : public SdcCmdComment
{
public:
  ClockGroups(const char *name,
	      bool logically_exclusive,
	      bool physically_exclusive,
	      bool asynchronous,
	      bool allow_paths,
	      const char *comment);
  ~ClockGroups();
  void makeClockGroup(ClockSet *clks);
  const char *name() const { return name_; }
  ClockGroupSet *groups() { return &groups_; }
  bool logicallyExclusive() const { return logically_exclusive_; }
  bool physicallyExclusive() const { return physically_exclusive_; }
  bool asynchronous() const { return asynchronous_; }
  bool allowPaths() const { return allow_paths_; }
  void removeClock(Clock *clk);

private:
  const char *name_;
  bool logically_exclusive_;
  bool physically_exclusive_;
  bool asynchronous_;
  bool allow_paths_;
  ClockGroupSet groups_;
};

} // namespace
