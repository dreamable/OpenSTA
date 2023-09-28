

#include "Sequential.hh"

#include "FuncExpr.hh"

namespace sta {

Sequential::Sequential(bool is_register,
		       FuncExpr *clock,
		       FuncExpr *data,
		       FuncExpr *clear,
		       FuncExpr *preset,
		       LogicValue clr_preset_out,
		       LogicValue clr_preset_out_inv,
		       LibertyPort *output,
		       LibertyPort *output_inv) :
  is_register_(is_register),
  clock_(clock),
  data_(data),
  clear_(clear),
  preset_(preset),
  clr_preset_out_(clr_preset_out),
  clr_preset_out_inv_(clr_preset_out_inv),
  output_(output),
  output_inv_(output_inv)
{
}

Sequential::~Sequential()
{
  if (clock_)
    clock_->deleteSubexprs();
  if (data_)
    data_->deleteSubexprs();
  if (clear_)
    clear_->deleteSubexprs();
  if (preset_)
    preset_->deleteSubexprs();
}

} // namespace
