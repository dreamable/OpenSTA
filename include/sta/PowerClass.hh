



namespace sta {

enum class PwrActivityOrigin
{
 global,
 input,
 user,
 propagated,
 clock,
 constant,
 defaulted,
 unknown
};

class PwrActivity
{
public:
  PwrActivity();
  PwrActivity(float activity,
	      float duty,
	      PwrActivityOrigin origin);
  float activity() const { return activity_; }
  void setActivity(float activity);
  float duty() const { return duty_; }
  void setDuty(float duty);
  PwrActivityOrigin origin() { return origin_; }
  const char *originName() const;
  void set(float activity,
	   float duty,
	   PwrActivityOrigin origin);
  bool isSet() const;

private:
  void check();

  // In general activity is per clock cycle, NOT per second.
  float activity_;
  float duty_;
  PwrActivityOrigin origin_;

  static constexpr float min_activity = 1E-10;
};

class PowerResult
{
public:
  PowerResult();
  void clear();
  float &internal() { return internal_; }
  float &switching() { return switching_; }
  float &leakage() { return leakage_; }
  float total() const;
  void incr(PowerResult &result);
  
private:
  float internal_;
  float switching_;
  float leakage_;
};

} // namespace
