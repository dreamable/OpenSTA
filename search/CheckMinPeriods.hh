



#include "NetworkClass.hh"
#include "GraphClass.hh"
#include "Delay.hh"
#include "SdcClass.hh"
#include "SearchClass.hh"
#include "StaState.hh"

namespace sta {

class MinPeriodCheckVisitor;

class CheckMinPeriods
{
public:
  explicit CheckMinPeriods(StaState *sta);
  ~CheckMinPeriods();
  void clear();
  MinPeriodCheckSeq &violations();
  // Min period check with the least slack.
  MinPeriodCheck *minSlackCheck();

protected:
  void visitMinPeriodChecks(MinPeriodCheckVisitor *visitor);
  void visitMinPeriodChecks(Vertex *vertex,
			    MinPeriodCheckVisitor *visitor);

  MinPeriodCheckSeq checks_;
  StaState *sta_;
};

class MinPeriodCheck
{
public:
  MinPeriodCheck(Pin *pin, Clock *clk);
  MinPeriodCheck *copy();
  Pin *pin() const { return pin_; }
  Clock *clk() const { return clk_; }
  float period() const;
  float minPeriod(const StaState *sta) const;
  Slack slack(const StaState *sta) const;

private:
  Pin *pin_;
  Clock *clk_;
};

class MinPeriodSlackLess
{
public:
  explicit MinPeriodSlackLess(StaState *sta);
  bool operator()(const MinPeriodCheck *check1,
		  const MinPeriodCheck *check2) const;

private:
 const StaState *sta_;
};

} // namespace
