



#include "TimingArc.hh"
#include "GraphClass.hh"
#include "SearchClass.hh"
#include "PathRef.hh"
#include "StaState.hh"

namespace sta {

class PathExpanded
{
public:
  PathExpanded(const StaState *sta);
  // Expand path for lookup by index.
  PathExpanded(const Path *path,
	       const StaState *sta);
  PathExpanded(const Path *path,
	       // Expand generated clk source paths.
	       bool expand_genclks,
	       const StaState *sta);
  void expand(const Path *path,
	      bool expand_genclks);
  size_t size() const { return paths_.size(); }
  // path(0) is the startpoint.
  // path(size()-1) is the endpoint.
  PathRef *path(size_t index);
  TimingArc *prevArc(size_t index);
  // Returns the path start point.
  //  Register/Latch Q pin
  //  Input pin
  PathRef *startPath();
  PathRef *startPrevPath();
  PathRef *endPath();
  TimingArc *startPrevArc();
  size_t startIndex() const;
  void clkPath(PathRef &clk_path);
  void latchPaths(// Return values.
		  PathRef *&d_path,
		  PathRef *&q_path,
		  Edge *&d_q_edge);

protected:
  void expandGenclk(PathRef *clk_path);
  // Convert external index that starts at the path root
  // and increases to an index for paths_ (reversed).
  size_t pathsIndex(size_t index) const;

  // The PathRefs in paths_ are in reverse order.
  //  paths_[0] is the endpoint.
  //  paths_[size-1] is the beginning of the path.
  PathRefSeq paths_;
  TimingArcSeq prev_arcs_;
  // Index of the startpoint.
  size_t start_index_;
  const StaState *sta_;
};

} // namespace
