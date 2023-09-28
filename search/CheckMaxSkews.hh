



#include "GraphClass.hh"
#include "Delay.hh"
#include "StaState.hh"
#include "SearchClass.hh"
#include "PathRef.hh"

namespace sta {

class MaxSkewCheckVisitor;

class CheckMaxSkews
{
public:
  explicit CheckMaxSkews(StaState *sta);
  ~CheckMaxSkews();
  void clear();
  // All violating max skew checks.
  MaxSkewCheckSeq &violations();
  // Max skew check with the least slack.
  MaxSkewCheck *minSlackCheck();

protected:
  void visitMaxSkewChecks(MaxSkewCheckVisitor *visitor);
  void visitMaxSkewChecks(Vertex *vertex,
			  MaxSkewCheckVisitor *visitor);

  MaxSkewCheckSeq checks_;
  StaState *sta_;
};

class MaxSkewCheck
{
public:
  MaxSkewCheck(PathVertex *clk_path,
	       PathVertex *ref_path,
	       TimingArc *check_arc,
	       Edge *check_edge);
  PathVertex *clkPath() { return &clk_path_; }
  Pin *clkPin(const StaState *sta) const;
  PathVertex *refPath() { return &ref_path_; }
  Pin *refPin(const StaState *sta) const;
  Delay skew(const StaState *sta) const;
  ArcDelay maxSkew(const StaState *sta) const;
  Slack slack(const StaState *sta) const;
  TimingArc *checkArc() const { return check_arc_; }

private:
  PathVertex clk_path_;
  PathVertex ref_path_;
  TimingArc *check_arc_;
  Edge *check_edge_;
};

class MaxSkewSlackLess
{
public:
  explicit MaxSkewSlackLess(const StaState *sta);
  bool operator()(const MaxSkewCheck *check1,
		  const MaxSkewCheck *check2) const;

protected:
  const StaState *sta_;
};

} // namespace
