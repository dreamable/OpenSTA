



#include "TimingModel.hh"

namespace sta {

class GateLinearModel : public GateTimingModel
{
public:
  GateLinearModel(float intrinsic, float resistance);
  void gateDelay(const LibertyCell *cell,
                 const Pvt *pvt,
                 float in_slew,
                 float load_cap,
                 float related_out_cap,
                 bool pocv_enabled,
                 // Return values.
                 ArcDelay &gate_delay,
                 Slew &drvr_slew) const override;
  string reportGateDelay(const LibertyCell *cell,
                         const Pvt *pvt,
                         float in_slew,
                         float load_cap,
                         float related_out_cap,
                         bool pocv_enabled,
                         int digits) const override;
  float driveResistance(const LibertyCell *cell,
                        const Pvt *pvt) const override;

protected:
  void setIsScaled(bool is_scaled) override;

  float intrinsic_;
  float resistance_;
};

class CheckLinearModel : public CheckTimingModel
{
public:
  explicit CheckLinearModel(float intrinsic);
  void checkDelay(const LibertyCell *cell,
                  const Pvt *pvt,
                  float from_slew,
                  float to_slew,
                  float related_out_cap,
                  bool pocv_enabled,
                  // Return values.
                  ArcDelay &margin) const override;
  string reportCheckDelay(const LibertyCell *cell,
                          const Pvt *pvt,
                          float from_slew,
                          const char *from_slew_annotation,
                          float to_slew,
                          float related_out_cap,
                          bool pocv_enabled,
                          int digits) const override;

protected:
  void setIsScaled(bool is_scaled) override;

  float intrinsic_;
};

} // namespace
