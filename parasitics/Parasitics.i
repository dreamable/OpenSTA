%module parasitics

%{



#include "Sta.hh"

using sta::Sta;
using sta::cmdLinkedNetwork;
using sta::Instance;
using sta::MinMaxAll;
using sta::ReducedParasiticType;
using sta::RiseFall;
using sta::Pin;

%}

%inline %{

bool
read_spef_cmd(const char *filename,
	      Instance *instance,
	      const Corner *corner,
              const MinMaxAll *min_max,
	      bool pin_cap_included,
	      bool keep_coupling_caps,
	      float coupling_cap_factor,
	      ReducedParasiticType reduce_to,
	      bool delete_after_reduce,
	      bool quiet)
{
  cmdLinkedNetwork();
  return Sta::sta()->readSpef(filename, instance, corner, min_max,
			      pin_cap_included, keep_coupling_caps,
                              coupling_cap_factor, reduce_to,
                              delete_after_reduce, quiet);
}

void
report_parasitic_annotation_cmd(bool report_unannotated,
                                const Corner *corner)
{
  cmdLinkedNetwork();
  Sta::sta()->reportParasiticAnnotation(report_unannotated, corner);
}

FloatSeq
find_pi_elmore(Pin *drvr_pin,
	       RiseFall *rf,
	       MinMax *min_max)
{
  float c2, rpi, c1;
  bool exists;
  Sta::sta()->findPiElmore(drvr_pin, rf, min_max, c2, rpi, c1, exists);
  FloatSeq pi_elmore;
  if (exists) {
    pi_elmore.push_back(c2);
    pi_elmore.push_back(rpi);
    pi_elmore.push_back(c1);
  }
  return pi_elmore;
}

float
find_elmore(Pin *drvr_pin,
	    Pin *load_pin,
	    RiseFall *rf,
	    MinMax *min_max)
{
  float elmore = 0.0;
  bool exists;
  Sta::sta()->findElmore(drvr_pin, load_pin, rf, min_max, elmore, exists);
  return elmore;
}

void
set_pi_model_cmd(Pin *drvr_pin,
		 RiseFall *rf,
		 MinMaxAll *min_max,
		 float c2,
		 float rpi,
		 float c1)
{
  Sta::sta()->makePiElmore(drvr_pin, rf, min_max, c2, rpi, c1);
}

void
set_elmore_cmd(Pin *drvr_pin,
	       Pin *load_pin,
	       RiseFall *rf,
	       MinMaxAll *min_max,
	       float elmore)
{
  Sta::sta()->setElmore(drvr_pin, load_pin, rf, min_max, elmore);
}

%} // inline
