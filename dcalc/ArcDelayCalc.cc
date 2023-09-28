

#include "ArcDelayCalc.hh"

#include "TimingModel.hh"
#include "TimingArc.hh"
#include "GraphDelayCalc.hh"

namespace sta {

ArcDelayCalc::ArcDelayCalc(StaState *sta):
  StaState(sta)
{
}

TimingModel *
ArcDelayCalc::model(const TimingArc *arc,
		    const DcalcAnalysisPt *dcalc_ap) const
{
  const OperatingConditions *op_cond = dcalc_ap->operatingConditions();
  const TimingArc *corner_arc = arc->cornerArc(dcalc_ap->libertyIndex());
  return corner_arc->model(op_cond);
}

GateTimingModel *
ArcDelayCalc::gateModel(const TimingArc *arc,
			const DcalcAnalysisPt *dcalc_ap) const
{
  return dynamic_cast<GateTimingModel*>(model(arc, dcalc_ap));
}

CheckTimingModel *
ArcDelayCalc::checkModel(const TimingArc *arc,
			 const DcalcAnalysisPt *dcalc_ap) const
{
  return dynamic_cast<CheckTimingModel*>(model(arc, dcalc_ap));
}

} // namespace
