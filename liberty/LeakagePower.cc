

#include "LeakagePower.hh"

#include "FuncExpr.hh"
#include "TableModel.hh"
#include "Liberty.hh"

namespace sta {

LeakagePowerAttrs::LeakagePowerAttrs() :
  when_(nullptr),
  power_(0.0)
{
}

void
LeakagePowerAttrs::setPower(float power)
{
  power_ = power;
}

////////////////////////////////////////////////////////////////

LeakagePower::LeakagePower(LibertyCell *cell,
			   LeakagePowerAttrs *attrs) :
  cell_(cell),
  when_(attrs->when()),
  power_(attrs->power())
{
  cell->addLeakagePower(this);
}

LeakagePower::~LeakagePower()
{
  if (when_)
    when_->deleteSubexprs();
}

} // namespace
