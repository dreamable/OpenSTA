

#include "PathAnalysisPt.hh"

#include "StringUtil.hh"
#include "Corner.hh"
#include "Search.hh"

namespace sta {

PathAnalysisPt::PathAnalysisPt(Corner *corner,
			       PathAPIndex index,
			       const MinMax *path_min_max,
			       DcalcAnalysisPt *dcalc_ap) :
  corner_(corner),
  index_(index),
  path_min_max_(path_min_max),
  tgt_clk_ap_(nullptr),
  dcalc_ap_(dcalc_ap)
{
}

void
PathAnalysisPt::setTgtClkAnalysisPt(PathAnalysisPt *path_ap)
{
  tgt_clk_ap_ = path_ap;
}

PathAnalysisPt *
PathAnalysisPt::insertionAnalysisPt(const EarlyLate *early_late) const
{
  return insertion_aps_[early_late->index()];
}

void
PathAnalysisPt::setInsertionAnalysisPt(const EarlyLate *early_late,
				       PathAnalysisPt *ap)
{
  insertion_aps_[early_late->index()] = ap;
}

} // namespace
