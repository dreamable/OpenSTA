



#include "Transition.hh"
#include "SearchClass.hh"
#include "PathVertexRep.hh"

namespace sta {

class PathVertex;

class ClkInfo
{
public:
  ClkInfo(const ClockEdge *clk_edge,
	  const Pin *clk_src,
	  bool is_propagated,
	  const Pin *gen_clk_src,
	  bool is_gen_clk_src_path,
	  const RiseFall *pulse_clk_sense,
	  Arrival insertion,
	  float latency,
	  ClockUncertainties *uncertainties,
          PathAPIndex path_ap_index,
	  PathVertexRep &crpr_clk_path,
	  const StaState *sta);
  ~ClkInfo();
  const char *asString(const StaState *sta) const;
  const ClockEdge *clkEdge() const { return clk_edge_; }
  const Clock *clock() const;
  const Pin *clkSrc() const { return clk_src_; }
  bool isPropagated() const { return is_propagated_; }
  const Pin *genClkSrc() const { return gen_clk_src_; }
  bool isPulseClk() const { return is_pulse_clk_; }
  RiseFall *pulseClkSense() const;
  int pulseClkSenseTrIndex() const { return pulse_clk_sense_; }
  float latency() const { return latency_; }
  Arrival &insertion() { return insertion_; }
  const Arrival &insertion() const { return insertion_; }
  ClockUncertainties *uncertainties() const { return uncertainties_; }
  PathAPIndex pathAPIndex() const { return path_ap_index_; }
  // Clock path for the last driver in the clock network used for
  // crpr resolution.
  PathVertexRep &crprClkPath() { return crpr_clk_path_; }
  const PathVertexRep &crprClkPath() const { return crpr_clk_path_; }
  VertexId crprClkVertexId() const;
  bool hasCrprClkPin() const { return !crpr_clk_path_.isNull(); }
  bool refsFilter(const StaState *sta) const;
  // This clk_info/tag is used for a generated clock source path.
  bool isGenClkSrcPath() const { return is_gen_clk_src_path_; }
  size_t hash() const { return hash_; }

protected:
  void findHash(const StaState *sta);

private:
  const ClockEdge *clk_edge_;
  const Pin *clk_src_;
  const Pin *gen_clk_src_;
  PathVertexRep crpr_clk_path_;
  ClockUncertainties *uncertainties_;
  Arrival insertion_;
  float latency_;
  size_t hash_;
  bool is_propagated_:1;
  bool is_gen_clk_src_path_:1;
  bool is_pulse_clk_:1;
  unsigned int pulse_clk_sense_:RiseFall::index_bit_count;
  unsigned int path_ap_index_:path_ap_index_bit_count;
};

class ClkInfoLess
{
public:
  explicit ClkInfoLess(const StaState *sta);
  ~ClkInfoLess() {}
  bool operator()(const ClkInfo *clk_info1,
		  const ClkInfo *clk_info2) const;

protected:
  const StaState *sta_;
};

class ClkInfoHash
{
public:
  size_t operator()(const ClkInfo *clk_info) const;
};

class ClkInfoEqual
{
public:
  ClkInfoEqual(const StaState *sta);
  bool operator()(const ClkInfo *clk_info1,
		  const ClkInfo *clk_info2) const;

protected:
  const StaState *sta_;
};

} // namespace
