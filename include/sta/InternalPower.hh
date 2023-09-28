



#include "LibertyClass.hh"
#include "Transition.hh"

namespace sta {

class InternalPowerAttrs;
class InternalPowerModel;

class InternalPowerAttrs
{
public:
  InternalPowerAttrs();
  virtual ~InternalPowerAttrs();
  void deleteContents();
  FuncExpr *when() const { return when_; }
  FuncExpr *&whenRef() { return when_; }
  void setModel(RiseFall *rf,
		InternalPowerModel *model);
  InternalPowerModel *model(RiseFall *rf) const;
  const char *relatedPgPin() const { return related_pg_pin_; }
  void setRelatedPgPin(const char *related_pg_pin);

protected:
  FuncExpr *when_;
  InternalPowerModel *models_[RiseFall::index_count];
  const  char *related_pg_pin_;
};

class InternalPower
{
public:
  InternalPower(LibertyCell *cell,
		LibertyPort *port,
		LibertyPort *related_port,
		InternalPowerAttrs *attrs);
  ~InternalPower();
  LibertyCell *libertyCell() const;
  LibertyPort *port() const { return port_; }
  LibertyPort *relatedPort() const { return related_port_; }
  FuncExpr *when() const { return when_; }
  const char *relatedPgPin() const { return related_pg_pin_; }
  float power(RiseFall *rf,
	      const Pvt *pvt,
	      float in_slew,
	      float load_cap);

protected:
  LibertyPort *port_;
  LibertyPort *related_port_;
  FuncExpr *when_;
  const  char *related_pg_pin_;
  InternalPowerModel *models_[RiseFall::index_count];
};

class InternalPowerModel
{
public:
  explicit InternalPowerModel(TableModel *model);
  ~InternalPowerModel();
  float power(const LibertyCell *cell,
	      const Pvt *pvt,
	      float in_slew,
	      float load_cap) const;
  string reportPower(const LibertyCell *cell,
                     const Pvt *pvt,
                     float in_slew,
                     float load_cap,
                     int digits) const;

protected:
  void findAxisValues(float in_slew,
		      float load_cap,
		      // Return values.
		      float &axis_value1,
		      float &axis_value2,
		      float &axis_value3) const;
  float axisValue(TableAxisPtr axis,
		  float in_slew,
		  float load_cap) const;
  bool checkAxes(const TableModel *model);
  bool checkAxis(TableAxisPtr axis);

  TableModel *model_;
};

} // namespace
