



#include "MinMax.hh"
#include "Transition.hh"
#include "NetworkClass.hh"
#include "SdcClass.hh"
#include "Sta.hh"

namespace sta {

class StaState;
class Corner;

class CheckCapacitanceLimits
{
public:
  CheckCapacitanceLimits(const Sta *sta);
  // corner=nullptr checks all corners.
  void checkCapacitance(const Pin *pin,
			const Corner *corner1,
			const MinMax *min_max,
			// Return values.
			// Corner is nullptr for no capacitance limit.
			const Corner *&corner,
			const RiseFall *&rf,
			float &capacitance,
			float &limit,
			float &slack) const;
  // Return pins with the min/max cap limit slack.
  // net=null check all nets
  // corner=nullptr checks all corners.
  PinSeq checkCapacitanceLimits(const Net *net,
                                bool violators,
                                const Corner *corner,
                                const MinMax *min_max);

protected:
  void checkCapacitance(const Pin *pin,
			const Corner *corner,
			const MinMax *min_max,
			const RiseFall *rf,
			float limit,
			// Return values.
			const Corner *&corner1,
			const RiseFall *&rf1,
			float &capacitance1,
			float &slack1,
			float &limit1) const;
  void checkCapacitance1(const Pin *pin,
                         const Corner *corner,
                         const MinMax *min_max,
                         // Return values.
                         const Corner *&corner1,
                         const RiseFall *&rf1,
                         float &capacitance1,
                         float &limit1,
                         float &slack1) const;
  void findLimit(const Pin *pin,
                 const Corner *corner,
		 const MinMax *min_max,
		 // Return values.
		 float &limit,
		 bool &limit_exists) const;
  void checkCapLimits(const Instance *inst,
                      bool violators,
                      const Corner *corner,
                      const MinMax *min_max,
                      PinSeq &cap_pins,
                      float &min_slack);
  void checkCapLimits(const Pin *pin,
                      bool violators,
                      const Corner *corner,
                      const MinMax *min_max,
                      PinSeq &cap_pins,
                      float &min_slack);
  bool checkPin(const Pin *pin);

  const Sta *sta_;
};

} // namespace
