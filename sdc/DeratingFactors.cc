

#include "DeratingFactors.hh"

namespace sta {

inline int
index(TimingDerateType type)
{
  return int(type);
}

inline int
index(TimingDerateCellType type)
{
  return int(type);
}

DeratingFactors::DeratingFactors()
{
  clear();
}

void
DeratingFactors::setFactor(PathClkOrData clk_data,
			   const RiseFallBoth *rf,
			   const EarlyLate *early_late,
			   float factor)
{
  for (auto tr1 : rf->range())
    factors_[int(clk_data)].setValue(tr1, early_late, factor);
}

void
DeratingFactors::factor(PathClkOrData clk_data,
			const RiseFall *rf,
			const EarlyLate *early_late,
			float &factor,
			bool &exists) const
{
  factors_[int(clk_data)].value(rf, early_late, factor, exists);
}

void
DeratingFactors::clear()
{
  for (int clk_data = 0; clk_data < path_clk_or_data_count;clk_data++)
    factors_[int(clk_data)].clear();
}

void
DeratingFactors::isOneValue(const EarlyLate *early_late,
			    bool &is_one_value,
			    float &value) const
{
  bool is_one_value0, is_one_value1;
  float value0, value1;
  is_one_value0 = factors_[0].isOneValue(early_late, value0);
  is_one_value1 = factors_[1].isOneValue(early_late, value1);
  is_one_value = is_one_value0
    && is_one_value1
    && value0 == value1;
  value = value1;
}

void
DeratingFactors::isOneValue(PathClkOrData clk_data,
			    const EarlyLate *early_late,
			    bool &is_one_value,
			    float &value) const
{
  is_one_value = factors_[int(clk_data)].isOneValue(early_late, value);
}

bool
DeratingFactors::hasValue() const
{
  return factors_[0].hasValue()
    || factors_[1].hasValue();
}

////////////////////////////////////////////////////////////////

DeratingFactorsGlobal::DeratingFactorsGlobal()
{
  clear();
}

void
DeratingFactorsGlobal::setFactor(TimingDerateType type,
				 PathClkOrData clk_data,
				 const RiseFallBoth *rf,
				 const EarlyLate *early_late,
				 float factor)
{
  factors_[index(type)].setFactor(clk_data, rf, early_late, factor);
}

void
DeratingFactorsGlobal::factor(TimingDerateType type,
			      PathClkOrData clk_data,
			      const RiseFall *rf,
			      const EarlyLate *early_late,
			      float &factor,
			      bool &exists) const
{
  factors_[index(type)].factor(clk_data, rf, early_late, factor, exists);
}

void
DeratingFactorsGlobal::factor(TimingDerateCellType type,
			      PathClkOrData clk_data,
			      const RiseFall *rf,
			      const EarlyLate *early_late,
			      float &factor,
			      bool &exists) const
{
  factors_[index(type)].factor(clk_data, rf, early_late, factor, exists);
}

void
DeratingFactorsGlobal::clear()
{
  for (int type = 0; type < timing_derate_type_count; type++)
    factors_[type].clear();
}

DeratingFactors *
DeratingFactorsGlobal::factors(TimingDerateType type)
{
  return &factors_[index(type)];
}

////////////////////////////////////////////////////////////////

DeratingFactorsCell::DeratingFactorsCell()
{
  clear();
}

void
DeratingFactorsCell::setFactor(TimingDerateCellType type,
			       PathClkOrData clk_data,
			       const RiseFallBoth *rf,
			       const EarlyLate *early_late,
			       float factor)
{
  factors_[index(type)].setFactor(clk_data, rf, early_late, factor);
}

void
DeratingFactorsCell::factor(TimingDerateCellType type,
			    PathClkOrData clk_data,
			    const RiseFall *rf,
			    const EarlyLate *early_late,
			    float &factor,
			    bool &exists) const
{
  factors_[index(type)].factor(clk_data, rf, early_late, factor, exists);
}

void
DeratingFactorsCell::clear()
{
  for (int type = 0; type < timing_derate_cell_type_count; type++)
    factors_[type].clear();
}

DeratingFactors *
DeratingFactorsCell::factors(TimingDerateCellType type)
{
  return &factors_[index(type)];
}

void
DeratingFactorsCell::isOneValue(const EarlyLate *early_late,
				bool &is_one_value,
				float &value) const
{
  bool is_one_value1, is_one_value2;
  float value1, value2;
  factors_[index(TimingDerateType::cell_delay)]
    .isOneValue(early_late, is_one_value1, value1);
  factors_[index(TimingDerateType::cell_check)]
    .isOneValue(early_late, is_one_value2, value2);
  is_one_value = is_one_value1
    && is_one_value2
    && value1 == value2;
  value = value1;
}

////////////////////////////////////////////////////////////////

DeratingFactorsNet::DeratingFactorsNet()
{
}

} // namespace
