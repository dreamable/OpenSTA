



#include "SdcClass.hh"
#include "SearchClass.hh"
#include "StaState.hh"
#include "PathRef.hh"

namespace sta {

class RiseFall;
class MinPulseWidthCheck;
class MinPulseWidthCheckVisitor;

class CheckMinPulseWidths
{
public:
  explicit CheckMinPulseWidths(StaState *sta);
  ~CheckMinPulseWidths();
  void clear();
  // Min pulse width checks for pins.
  // corner=nullptr checks all corners.
  MinPulseWidthCheckSeq &check(PinSeq *pins,
			       const Corner *corner);
  // All min pulse width checks.
  // corner=nullptr checks all corners.
  MinPulseWidthCheckSeq &check(const Corner *corner);
  // All violating min pulse width checks.
  // corner=nullptr checks all corners.
  MinPulseWidthCheckSeq &violations(const Corner *corner);
  // Min pulse width check with the least slack.
  // corner=nullptr checks all corners.
  MinPulseWidthCheck *minSlackCheck(const Corner *corner);

protected:
  void visitMinPulseWidthChecks(MinPulseWidthCheckVisitor *visitor);
  void visitMinPulseWidthChecks(Vertex *vertex,
				MinPulseWidthCheckVisitor *visitor);

  MinPulseWidthCheckSeq checks_;
  StaState *sta_;
};

class MinPulseWidthCheck
{
public:
  explicit MinPulseWidthCheck();
  MinPulseWidthCheck(Path *open_path);
  MinPulseWidthCheck *copy();
  Pin *pin(const StaState *sta) const;
  const RiseFall *openTransition(const StaState *sta) const;
  Arrival width(const StaState *sta) const;
  float minWidth(const StaState *sta) const;
  Slack slack(const StaState *sta) const;
  Path *openPath() { return &open_path_; }
  Corner *corner(const StaState *sta) const;
  const Path *openPath() const { return &open_path_; }
  Arrival openArrival(const StaState *sta) const;
  void closePath(const StaState *sta,
		 // Return value.
		 PathVertex &close) const;
  Arrival closeArrival(const StaState *sta) const;
  Arrival openDelay(const StaState *sta) const;
  Arrival closeDelay(const StaState *sta) const;
  float closeOffset(const StaState *sta) const;
  const ClockEdge *openClkEdge(const StaState *sta) const;
  const ClockEdge *closeClkEdge(const StaState *sta) const;
  Crpr commonClkPessimism(const StaState *sta) const;

protected:
  // Open path of the pulse.
  PathRef open_path_;
};

class MinPulseWidthSlackLess
{
public:
  explicit MinPulseWidthSlackLess(const StaState *sta);
  bool operator()(const MinPulseWidthCheck *check1,
		  const MinPulseWidthCheck *check2) const;

private:
  const StaState *sta_;
};

} // namespace
