



#include "MinMax.hh"
#include "LibertyClass.hh"
#include "NetworkClass.hh"
#include "NetworkCmp.hh"
#include "SdcClass.hh"
#include "RiseFallMinMax.hh"

namespace sta {

class DataCheck
{
public:
  DataCheck(Pin *from,
	    Pin *to,
	    Clock *clk);
  Pin *from() const { return from_; }
  Pin *to() const { return to_; }
  Clock *clk() const { return clk_; }
  void margin(const RiseFall *from_rf,
	      const RiseFall *to_rf,
	      const SetupHold *setup_hold,
	      // Return values.
	      float &margin,
	      bool &exists) const;
  void setMargin(const RiseFallBoth *from_rf,
		 const RiseFallBoth *to_rf,
		 const SetupHoldAll *setup_hold,
		 float margin);
  void removeMargin(const RiseFallBoth *from_rf,
		    const RiseFallBoth *to_rf,
		    const SetupHoldAll *setup_hold);
  bool empty() const;
  void marginIsOneValue(SetupHold *setup_hold,
			// Return values.
			float &value,
			bool &one_value) const;

private:
  Pin *from_;
  Pin *to_;
  Clock *clk_;
  RiseFallMinMax margins_[RiseFall::index_count];
};

class DataCheckLess
{
public:
  DataCheckLess(const Network *network);
  bool operator()(const DataCheck *check1,
		  const DataCheck *check2) const;

private:
  const Network *network_;
};

} // namespace
