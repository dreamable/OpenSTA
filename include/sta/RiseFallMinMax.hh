



#include "MinMax.hh"
#include "Transition.hh"

namespace sta {

// Rise/Fall/Min/Max group of four values common to many constraints.
class RiseFallMinMax
{
public:
  RiseFallMinMax();
  RiseFallMinMax(const RiseFallMinMax *rfmm);
  explicit RiseFallMinMax(float init_value);
  float value(const RiseFall *rf,
	      const MinMax *min_max) const;
  float value(const MinMax *min_max) const;
  void value(const RiseFall *rf,
	     const MinMax *min_max,
	     float &value,
	     bool &exists) const;
  bool hasValue() const;
  void maxValue(// Return values
		float &max_value,
		bool &exists) const;
  bool empty() const;
  bool hasValue(const RiseFall *rf,
		const MinMax *min_max) const;
  void setValue(const RiseFallBoth *rf,
		const MinMaxAll *min_max,
		float value);
  void setValue(const RiseFallBoth *rf,
		const MinMax *min_max,
		float value);
  void setValue(const RiseFall *rf,
		const MinMax *min_max, float value);
  void setValue(float value);
  void mergeValue(const RiseFallBoth *rf,
		  const MinMaxAll *min_max,
		  float value);
  void mergeValue(const RiseFall *rf,
		  const MinMax *min_max,
		  float value);
  void setValues(RiseFallMinMax *values);
  void removeValue(const RiseFallBoth *rf,
		   const MinMax *min_max);
  void removeValue(const RiseFallBoth *rf, 
		   const MinMaxAll *min_max);
  // Merge all values of rfmm.
  void mergeWith(RiseFallMinMax *rfmm);
  void clear();
  bool equal(const RiseFallMinMax *values) const;
  bool isOneValue() const;
  bool isOneValue(float &value) const;
  bool isOneValue(const MinMax *min_max,
		  // Return values.
		  float &value) const;

private:
  float values_[RiseFall::index_count][MinMax::index_count];
  bool exists_[RiseFall::index_count][MinMax::index_count];
};

} // namespace
