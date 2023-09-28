

#include "RiseFallValues.hh"

namespace sta {

RiseFallValues::RiseFallValues()
{
  clear();
}

void
RiseFallValues::clear()
{
  for (auto tr_index : RiseFall::rangeIndex())
    exists_[tr_index] = false;
}

RiseFallValues::RiseFallValues(float init_value)
{
  for (auto tr_index : RiseFall::rangeIndex()) {
    values_[tr_index] = init_value;
    exists_[tr_index] = true;
  }
}

void
RiseFallValues::setValue(float value)
{
  setValue(RiseFallBoth::riseFall(), value);
}

void
RiseFallValues::setValue(const RiseFallBoth *rf,
			 float value)
{
  for (auto rf_index : rf->rangeIndex()) {
    values_[rf_index] = value;
    exists_[rf_index] = true;
  }
}

void
RiseFallValues::setValue(const RiseFall *rf,
			 float value)
{
  int rf_index = rf->index();
  values_[rf_index] = value;
  exists_[rf_index] = true;
}

void
RiseFallValues::setValues(RiseFallValues *values)
{
  for (auto rf_index : RiseFall::rangeIndex()) {
    values_[rf_index] = values->values_[rf_index];
    exists_[rf_index] = values->exists_[rf_index];
  }
}

void
RiseFallValues::value(const RiseFall *rf,
		      float &value, bool &exists) const
{
  int rf_index = rf->index();
  exists = exists_[rf_index];
  if (exists)
    value = values_[rf_index];
}

float
RiseFallValues::value(const RiseFall *rf) const
{
  return values_[rf->index()];
}

bool
RiseFallValues::hasValue(const RiseFall *rf) const
{
  return exists_[rf->index()];
}

} // namespace
