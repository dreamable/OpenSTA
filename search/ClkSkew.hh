



#include "Map.hh"
#include "SdcClass.hh"
#include "StaState.hh"
#include "SearchClass.hh"

namespace sta {

class ClkSkew;

typedef Map<const Clock*, ClkSkew*> ClkSkewMap;

// Find and report min clock skews.
class ClkSkews : public StaState
{
public:
  ClkSkews(StaState *sta);
  // Report clk skews for clks.
  void reportClkSkew(ClockSet *clks,
		     const Corner *corner,
		     const SetupHold *setup_hold,
		     int digits);
  // Find worst clock skew.
  float findWorstClkSkew(const Corner *corner,
                         const SetupHold *setup_hold);

protected:
  void findClkSkew(ClockSet *clks,
		   const Corner *corner,
		   const SetupHold *setup_hold,
		   ClkSkewMap &skews);
  bool hasClkPaths(Vertex *vertex,
		   ClockSet *clks);
  void findClkSkewFrom(Vertex *src_vertex,
		       Vertex *q_vertex,
		       RiseFallBoth *src_rf,
		       ClockSet *clks,
		       const Corner *corner,
		       const SetupHold *setup_hold,
		       ClkSkewMap &skews);
  void findClkSkew(Vertex *src_vertex,
		   RiseFallBoth *src_rf,
		   Vertex *tgt_vertex,
		   RiseFallBoth *tgt_rf,
		   ClockSet *clks,
		   const Corner *corner,
		   const SetupHold *setup_hold,
		   ClkSkewMap &skews);
  VertexSet findFanout(Vertex *from);
};
    
} // namespace
