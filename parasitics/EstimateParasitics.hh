



#include "LibertyClass.hh"
#include "NetworkClass.hh"
#include "SdcClass.hh"
#include "ParasiticsClass.hh"

namespace sta {

class Corner;
class StaState;

class EstimateParasitics
{
public:

protected:
  // Helper function for wireload estimation.
  void estimatePiElmore(const Pin *drvr_pin,
			const RiseFall *rf,
			const Wireload *wireload,
			float fanout,
			float net_pin_cap,
			const OperatingConditions *op_cond,
			const Corner *corner,
			const MinMax *min_max,
			const StaState *sta,
			// Return values.
			float &c2,
			float &rpi,
			float &c1,
			float &elmore_res,
			float &elmore_cap,
			bool &elmore_use_load_cap);
  void estimatePiElmoreBest(const Pin *drvr_pin,
			    float net_pin_cap,
			    float wireload_cap,
			    const RiseFall *rf,
			    const OperatingConditions *op_cond,
			    const Corner *corner,
			    const MinMax *min_max,
			    // Return values.
			    float &c2,
			    float &rpi,
			    float &c1,
			    float &elmore_res,
			    float &elmore_cap,
			    bool &elmore_use_load_cap) const;
  void estimatePiElmoreWorst(const Pin *drvr_pin,
			     float wireload_cap,
			     float wireload_res,
			     float fanout,
			     float net_pin_cap,
			     const RiseFall *rf,
			     const OperatingConditions *op_cond,
			     const Corner *corner,
			     const MinMax *min_max,
			     const StaState *sta,
			     // Return values.
			     float &c2, float &rpi, float &c1,
			     float &elmore_res, float &elmore_cap,
			     bool &elmore_use_load_cap);
  void estimatePiElmoreBalanced(const Pin *drvr_pin,
				float wireload_cap,
				float wireload_res,
				float fanout,
				float net_pin_cap,
				const RiseFall *rf,
				const OperatingConditions *op_cond,
				const Corner *corner,
				const MinMax *min_max,
				const StaState *sta,
				// Return values.
				float &c2, float &rpi, float &c1,
				float &elmore_res, float &elmore_cap,
				bool &elmore_use_load_cap);
};

} // namespace
