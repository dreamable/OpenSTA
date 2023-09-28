%module dcalc

%{



#include "Sta.hh"

%}

%inline %{

StringSeq
delay_calc_names()
{
  return sta::delayCalcNames();
}

bool
is_delay_calc_name(const char *alg)
{
  return sta::isDelayCalcName(alg);
}

void
set_delay_calculator_cmd(const char *alg)
{
  sta::Sta::sta()->setArcDelayCalc(alg);
}

void
set_delay_calc_incremental_tolerance(float tol)
{
  sta::Sta::sta()->setIncrementalDelayTolerance(tol);
}

string
report_delay_calc_cmd(Edge *edge,
		      TimingArc *arc,
		      const Corner *corner,
		      const MinMax *min_max,
		      int digits)
{
  cmdLinkedNetwork();
  return Sta::sta()->reportDelayCalc(edge, arc, corner, min_max, digits);
}

%} // inline
