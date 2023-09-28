



namespace sta {

// Constraints::pinNetCap return values.
class NetCaps
{
public:
  NetCaps();
  NetCaps(float pin_cap,
	  float wire_cap,
	  float fanout,
	  bool has_set_load);
  void init(float pin_cap,
	    float wire_cap,
	    float fanout,
	    bool has_set_load);
  float pinCap() const { return pin_cap_; }
  float wireCap() const{ return wire_cap_; }
  float fanout() const{ return fanout_; }
  bool hasSetLoad() const { return has_set_load_; }

private:
  float pin_cap_;
  float wire_cap_;
  float fanout_;
  bool has_set_load_;
};

} // namespace
