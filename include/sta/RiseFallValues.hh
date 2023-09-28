



#include "Transition.hh"

namespace sta {

// Rise/fall group of two values.
class RiseFallValues
{
public:
  RiseFallValues();
  explicit RiseFallValues(float init_value);
  float value(const RiseFall *rf) const;
  void value(const RiseFall *rf,
	     float &value, bool &exists) const;
  bool hasValue(const RiseFall *rf) const;
  void setValue(const RiseFallBoth *rf, float value);
  void setValue(const RiseFall *rf, float value);
  void setValue(float value);
  void setValues(RiseFallValues *values);
  void clear();

private:
  float values_[RiseFall::index_count];
  bool exists_[RiseFall::index_count];
};

} // namespace
