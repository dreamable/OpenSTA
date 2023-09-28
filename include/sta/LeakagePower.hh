



#include "LibertyClass.hh"

namespace sta {

class LeakagePowerAttrs;

class LeakagePowerAttrs
{
public:
  LeakagePowerAttrs();
  FuncExpr *when() const { return when_; }
  FuncExpr *&whenRef() { return when_; }
  float power() { return power_; }
  void setPower(float power);

protected:
  FuncExpr *when_;
  float power_;
};

class LeakagePower
{
public:
  LeakagePower(LibertyCell *cell,
	       LeakagePowerAttrs *attrs);
  ~LeakagePower();
  LibertyCell *libertyCell() const { return cell_; }
  FuncExpr *when() const { return when_; }
  float power() { return power_; }

protected:
  LibertyCell *cell_;
  FuncExpr *when_;
  float power_;
};

} // namespace
