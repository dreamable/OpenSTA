



#include "MinMax.hh"
#include "NetworkClass.hh"
#include "SdcClass.hh"
#include "Sta.hh"

namespace sta {

class StaState;

class CheckFanoutLimits
{
public:
  CheckFanoutLimits(const Sta *sta);
  void checkFanout(const Pin *pin,
		   const MinMax *min_max,
		   // Return values.
		   float &fanout,
		   float &limit,
		   float &slack) const;
  // Return pins with the min/max fanout limit slack.
  // net=null check all nets
  // corner=nullptr checks all corners.
  PinSeq checkFanoutLimits(const Net *net,
                           bool violators,
                           const MinMax *min_max);

protected:
  void checkFanout(const Pin *pin,
		   const MinMax *min_max,
		   float limit1,
		   // Return values.
		   float &fanout,
		   float &limit,
		   float &slack) const;
  void findLimit(const Pin *pin,
		 const MinMax *min_max,
		 // Return values.
		 float &limit,
		 bool &limit_exists) const;
  float fanoutLoad(const Pin *pin) const;
  void checkFanoutLimits(const Instance *inst,
                         bool violators,
                         const MinMax *min_max,
                         PinSeq &fanout_pins,
                         float &min_slack);
  void checkFanoutLimits(const Pin *pin,
                         bool violators,
                         const MinMax *min_max,
                         PinSeq &fanout_pins,
                         float &min_slack);
  bool checkPin(const Pin *pin);

  const Sta *sta_;
};

} // namespace
