

#include "StringUtil.hh"
#include "DcalcAnalysisPt.hh"
#include "Corner.hh"

namespace sta {

DcalcAnalysisPt::DcalcAnalysisPt(Corner *corner,
				 DcalcAPIndex index,
				 const OperatingConditions *op_cond,
				 const MinMax *min_max,
				 const MinMax *check_clk_slew_min_max) :
  corner_(corner),
  index_(index),
  op_cond_(op_cond),
  min_max_(min_max),
  check_clk_slew_min_max_(check_clk_slew_min_max)
{
}

void
DcalcAnalysisPt::setOperatingConditions(const OperatingConditions *op_cond)
{
  op_cond_ = op_cond;
}

ParasiticAnalysisPt *
DcalcAnalysisPt::parasiticAnalysisPt() const
{
  return corner_->findParasiticAnalysisPt(min_max_);
}

void
DcalcAnalysisPt::setCheckClkSlewIndex(DcalcAPIndex index)
{
  check_clk_slew_index_ = index;
}

int 
DcalcAnalysisPt::libertyIndex() const
{
  return corner_->libertyIndex(min_max_);
}

} // namespace
