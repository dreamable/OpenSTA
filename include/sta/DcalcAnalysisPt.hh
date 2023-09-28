



#include "Iterator.hh"
#include "MinMax.hh"
#include "LibertyClass.hh"
#include "SdcClass.hh"
#include "ParasiticsClass.hh"
#include "GraphClass.hh"
#include "StaState.hh"

namespace sta {

class Corner;

// Delay calculation analysis point.
// This collects all of the parameters used to find one set of
// delay calculation results.
class DcalcAnalysisPt
{
public:
  DcalcAnalysisPt(Corner *corner,
		  DcalcAPIndex index,
		  const OperatingConditions *op_cond,
		  const MinMax *min_max,
		  const MinMax *check_clk_slew_min_max);
  Corner *corner() const { return corner_; }
  // Which of the delay_count results this analysis point corresponds to.
  DcalcAPIndex index() const { return index_; }
  // Slew index of timing check data.
  DcalcAPIndex checkDataSlewIndex() const { return index_; }
  // Slew index of timing check clock.
  DcalcAPIndex checkClkSlewIndex() const { return check_clk_slew_index_; }
  // Slew min/max of timing check clock.
  const MinMax *checkClkSlewMinMax() const { return check_clk_slew_min_max_; }
  // Constraint min/max values to use.
  const MinMax *constraintMinMax() const { return min_max_; }
  // Constraints::operatingCondition(cnst_min_max_)
  const OperatingConditions *operatingConditions() const { return op_cond_; }
  void setOperatingConditions(const OperatingConditions *op_cond);
  // Delay merging min/max operator (for wires).
  const MinMax *delayMinMax() const { return min_max_; }
  // Merge min/max slews across timing arcs.
  const MinMax *slewMinMax() const { return min_max_; }
  ParasiticAnalysisPt *parasiticAnalysisPt() const;
  void setCheckClkSlewIndex(DcalcAPIndex index);
  int libertyIndex() const;

private:
  Corner *corner_;
  DcalcAPIndex index_;
  DcalcAPIndex check_clk_slew_index_;
  const OperatingConditions *op_cond_;
  const MinMax *min_max_;
  const MinMax *check_clk_slew_min_max_;
};

} // namespace
