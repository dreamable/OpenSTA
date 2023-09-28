



#include "MinMax.hh"
#include "LibertyClass.hh"
#include "SdcClass.hh"
#include "RiseFallMinMax.hh"

namespace sta {

class DeratingFactors
{
public:
  DeratingFactors();
  void setFactor(PathClkOrData clk_data,
		 const RiseFallBoth *rf,
		 const EarlyLate *early_late,
		 float factor);
  void factor(PathClkOrData clk_data,
	      const RiseFall *rf,
	      const EarlyLate *early_late,
	      float &factor,
	      bool &exists) const;
  void clear();
  void isOneValue(const EarlyLate *early_late,
		  bool &is_one_value,
		  float &value) const;
  void isOneValue(PathClkOrData clk_data,
		  const EarlyLate *early_late,
		  bool &is_one_value,
		  float &value) const;
  bool hasValue() const;

private:
  RiseFallMinMax factors_[path_clk_or_data_count];
};

class DeratingFactorsGlobal
{
public:
  DeratingFactorsGlobal();
  void setFactor(TimingDerateType type,
		 PathClkOrData clk_data,
		 const RiseFallBoth *rf,
		 const EarlyLate *early_late,
		 float factor);
  void factor(TimingDerateType type,
	      PathClkOrData clk_data,
	      const RiseFall *rf,
	      const EarlyLate *early_late,
	      float &factor,
	      bool &exists) const;
  void factor(TimingDerateCellType type,
	      PathClkOrData clk_data,
	      const RiseFall *rf,
	      const EarlyLate *early_late,
	      float &factor,
	      bool &exists) const;
  DeratingFactors *factors(TimingDerateType type);
  void clear();

private:
  DeratingFactors factors_[timing_derate_type_count];
};

class DeratingFactorsCell
{
public:
  DeratingFactorsCell();
  void setFactor(TimingDerateCellType type,
		 PathClkOrData clk_data,
		 const RiseFallBoth *rf,
		 const EarlyLate *early_late,
		 float factor);
  void factor(TimingDerateCellType type,
	      PathClkOrData clk_data,
	      const RiseFall *rf,
	      const EarlyLate *early_late,
	      float &factor,
	      bool &exists) const;
  DeratingFactors *factors(TimingDerateCellType type);
  void clear();
  void isOneValue(const EarlyLate *early_late,
		  bool &is_one_value,
		  float &value) const;

private:
  DeratingFactors factors_[timing_derate_cell_type_count];
};

class DeratingFactorsNet : public DeratingFactors
{
public:
  DeratingFactorsNet();
};

} // namespace
