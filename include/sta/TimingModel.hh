



#include <string>

#include "Delay.hh"
#include "LibertyClass.hh"

namespace sta {

using std::string;

// Abstract base class for GateTimingModel and CheckTimingModel.
class TimingModel
{
public:
  virtual ~TimingModel() {}

protected:
  virtual void setIsScaled(bool is_scaled) = 0;

  friend class LibertyCell;
};

// Abstract base class for LinearModel and TableModel.
class GateTimingModel : public TimingModel
{
public:
  // Gate delay calculation.
  virtual void gateDelay(const LibertyCell *cell,
			 const Pvt *pvt,
			 float in_slew,
			 float load_cap,
			 float related_out_cap,
			 bool pocv_enabled,
			 // Return values.
			 ArcDelay &gate_delay,
			 Slew &drvr_slew) const = 0;
  virtual string reportGateDelay(const LibertyCell *cell,
                                 const Pvt *pvt,
                                 float in_slew,
                                 float load_cap,
                                 float related_out_cap,
                                 bool pocv_enabled,
                                 int digits) const = 0;
  virtual float driveResistance(const LibertyCell *cell,
				const Pvt *pvt) const = 0;
};

// Abstract base class for timing check timing models.
class CheckTimingModel : public TimingModel
{
public:
  // Timing check margin delay calculation.
  virtual void checkDelay(const LibertyCell *cell,
			  const Pvt *pvt,
			  float from_slew,
			  float to_slew,
			  float related_out_cap,
			  bool pocv_enabled,
			  // Return values.
			  ArcDelay &margin) const = 0;
  virtual string reportCheckDelay(const LibertyCell *cell,
                                  const Pvt *pvt,
                                  float from_slew,
                                  const char *from_slew_annotation,
                                  float to_slew,
                                  float related_out_cap,
                                  bool pocv_enabled,
                                  int digits) const = 0;
};

} // namespace
