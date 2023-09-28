



#include "MinMax.hh"
#include "Transition.hh"
#include "NetworkClass.hh"
#include "GraphClass.hh"
#include "Delay.hh"
#include "SdcClass.hh"

namespace sta {

class StaState;
class DcalcAnalysisPt;
class Corner;

class CheckSlewLimits
{
public:
  CheckSlewLimits(const StaState *sta);
  // corner=nullptr checks all corners.
  void checkSlew(const Pin *pin,
		 const Corner *corner,
		 const MinMax *min_max,
		 bool check_clks,
		 // Return values.
		 // Corner is nullptr for no slew limit.
		 const Corner *&corner1,
		 const RiseFall *&rf,
		 Slew &slew,
		 float &limit,
		 float &slack) const;
  // Return pins with the min/max slew limit slack.
  // net=null check all nets
  // corner=nullptr checks all corners.
  PinSeq checkSlewLimits(const Net *net,
                         bool violators,
                         const Corner *corner,
                         const MinMax *min_max);
  void findLimit(const LibertyPort *port,
                 const Corner *corner,
                 const MinMax *min_max,
                 // Return values.
                 float &limit,
                 bool &exists) const;

protected:
  void checkSlews1(const Pin *pin,
		   const Corner *corner,
		   const MinMax *min_max,
		   bool check_clks,
		   // Return values.
		   const Corner *&corner1,
		   const RiseFall *&rf1,
		   Slew &slew1,
		   float &limit1,
		   float &slack1) const;
  void checkSlews1(Vertex *vertex,
		   const Corner *corner,
		   const MinMax *min_max,
		   bool check_clks,
		   // Return values.
		   const Corner *&corner1,
		   const RiseFall *&rf1,
		   Slew &slew1,
		   float &limit1,
		   float &slack1) const;
  void checkSlew(Vertex *vertex,
		 const Corner *corner1,
		 const RiseFall *rf1,
		 const MinMax *min_max,
		 float limit1,
		 // Return values.
		 const Corner *&corner,
		 const RiseFall *&rf,
		 Slew &slew,
		 float &slack,
		 float &limit) const;
  void findLimit(const Pin *pin,
		 const Vertex *vertex,
                 const Corner *corner,
		 const RiseFall *rf,
		 const MinMax *min_max,
		 bool check_clks,
		 // Return values.
		 float &limit,
		 bool &limit_exists) const;
  void checkSlewLimits(const Instance *inst,
                       bool violators,
                       const Corner *corner,
                       const MinMax *min_max,
                       PinSeq &slew_pins,
                       float &min_slack);
  void checkSlewLimits(const Pin *pin,
                       bool violators,
                       const Corner *corner,
                       const MinMax *min_max,
                       PinSeq &slew_pins,
                       float &min_slack);
  void clockDomains(const Vertex *vertex,
		    // Return value.
		    ClockSet &clks) const;

  const StaState *sta_;
};

} // namespace
