



#include "SdcClass.hh"
#include "GraphClass.hh"
#include "SearchClass.hh"
#include "StaState.hh"

namespace sta {

typedef Set<FuncExpr*> FuncExprSet;

class GatedClk : public StaState
{
public:
  GatedClk(const StaState *sta);

  bool isGatedClkEnable(Vertex *vertex) const;
  void isGatedClkEnable(Vertex *enable_vertex,
			bool &is_gated_clk_enable,
			const Pin *&clk_pin,
			LogicValue &logic_active_value) const;
  void gatedClkEnables(Vertex *clk_vertex,
		       // Return value.
		       PinSet &enable_pins);
  RiseFall *gatedClkActiveTrans(LogicValue active_value,
				     const MinMax *min_max) const;

protected:
  void isClkGatingFunc(FuncExpr *func,
		       LibertyPort *enable_port,
		       LibertyPort *clk_port,
		       bool &is_clk_gate,
		       LogicValue &logic_value) const;
  void functionClkOperands(FuncExpr *root_expr,
			   FuncExpr *curr_expr,
			   FuncExprSet &funcs) const;
};

} // namespace
