



#include "Iterator.hh"
#include "MinMax.hh"
#include "SdcClass.hh"
#include "SearchClass.hh"

namespace sta {

class MinMax;
class DcalcAnalysisPt;
class Corner;

class PathAnalysisPt
{
public:
  PathAnalysisPt(Corner *corner,
		 PathAPIndex index,
		 const MinMax *path_min_max,
		 DcalcAnalysisPt *dcalc_ap);
  Corner *corner() const { return corner_; }
  PathAPIndex index() const { return index_; }
  const MinMax *pathMinMax() const { return path_min_max_; }
  // Converging path arrival merging.
  const MinMax *mergeMinMax() const { return path_min_max_; }
  // Path analysis point for timing check target clock arrivals.
  PathAnalysisPt *tgtClkAnalysisPt() const { return tgt_clk_ap_; }
  void setTgtClkAnalysisPt(PathAnalysisPt *path_ap);
  DcalcAnalysisPt *dcalcAnalysisPt() const { return dcalc_ap_; }
  PathAnalysisPt *insertionAnalysisPt(const EarlyLate *early_late) const;
  void setInsertionAnalysisPt(const EarlyLate *early_late, PathAnalysisPt *ap);

private:
  Corner *corner_;
  PathAPIndex index_;
  const MinMax *path_min_max_;
  PathAnalysisPt *tgt_clk_ap_;
  PathAnalysisPt *insertion_aps_[EarlyLate::index_count];
  DcalcAnalysisPt *dcalc_ap_;
};

} // namespace
