



#include "NetworkClass.hh"
#include "GraphClass.hh"
#include "LibertyClass.hh"
#include "StaState.hh"

namespace sta {

// Class hierarchy:
// SearchPred
//  SearchPred0 (unless disabled or constant)
//   EvalPred (unless timing check)
//    SearchThru (unless latch D->Q, outside vertex subset)
//   SearchPred1 (unless loop disabled)
//    ClkTreeSearchPred (only wire or combinational)
//    SearchPred2 (unless timing check)
//     SearchPredNonLatch2 (unless latch D->Q)
//     SearchPredNonReg2 (unless reg CLK->Q, latch D->Q)

// Virtual base class for search predicates.
class SearchPred
{
public:
  SearchPred() {}
  virtual ~SearchPred() {}
  // Search is allowed from from_vertex.
  virtual bool searchFrom(const Vertex *from_vertex) = 0;
  // Search is allowed through edge.
  // from/to pins are NOT checked.
  // inst can be either the from_pin or to_pin instance because it
  // is only referenced when they are the same (non-wire edge).
  virtual bool searchThru(Edge *edge) = 0;
  // Search is allowed to to_pin.
  virtual bool searchTo(const Vertex *to_vertex) = 0;
};

class SearchPred0 : public SearchPred
{
public:
  explicit SearchPred0(const StaState *sta);
  // Search from a vertex unless
  //  disabled by constraint
  //  constant logic zero/one
  virtual bool searchFrom(const Vertex *from_vertex);
  // Search thru an edge unless
  //  traverses disabled from/to pin pair
  //  disabled by condition expression
  //  wire that traverses a disabled hierarchical pin
  //  register set/reset edge (and search thru them is disabled)
  //  cond expression is disabled
  //  non-controlling constant values on other pins that disable the
  //    edge (such as a mux select)
  virtual bool searchThru(Edge *edge);
  // Search to a vertex unless
  //  constant logic zero/one
  virtual bool searchTo(const Vertex *to_vertex);

protected:
  const StaState *sta_;
};

// SearchPred0 unless
//  disabled to break combinational loop
class SearchPred1 : public SearchPred0
{
public:
  explicit SearchPred1(const StaState *sta);
  virtual bool searchThru(Edge *edge);
};

// SearchPred1 unless
//  timing check edge
class SearchPred2 : public SearchPred1
{
public:
  explicit SearchPred2(const StaState *sta);
  virtual bool searchThru(Edge *edge);
};

// SearchPred2 unless
//  latch D->Q edge
class SearchPredNonLatch2 : public SearchPred2
{
public:
  explicit SearchPredNonLatch2(const StaState *sta);
  virtual bool searchThru(Edge *edge);
};

// SearchPred2 unless
//  register/latch CLK->Q edges.
class SearchPredNonReg2 : public SearchPred2
{
public:
  explicit SearchPredNonReg2(const StaState *sta);
  virtual bool searchThru(Edge *edge);
};

// Predicate for BFS search to stop at the end of the clock tree.
// Search only thru combinational gates and wires.
class ClkTreeSearchPred : public SearchPred1
{
public:
  explicit ClkTreeSearchPred(const StaState *sta);
  virtual bool searchThru(Edge *edge);
};

bool
isClkEnd(Vertex *vertex, Graph *graph);

// Predicate to see if arc/edge is disabled by constants on other pins
// that effect the unateness of the edge.
bool
searchThru(const Edge *edge,
	   const TimingArc *arc,
	   const Graph *graph);
bool
searchThru(Vertex *from_vertex,
	   const RiseFall *from_rf,
	   const Edge *edge,
	   Vertex *to_vertex,
	   const RiseFall *to_rf);


////////////////////////////////////////////////////////////////

bool
hasFanin(Vertex *vertex,
	 SearchPred *pred,
	 const Graph *graph);

// Vertices with no fanout have at no enabled (non-disabled) edges
// leaving them.
bool
hasFanout(Vertex *vertex,
	  SearchPred *pred,
	  const Graph *graph);

} // namespace
