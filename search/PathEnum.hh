



#include <queue>

#include "Iterator.hh"
#include "Vector.hh"
#include "StaState.hh"
#include "SearchClass.hh"
#include "Path.hh"

namespace sta {

class Diversion;
class PathEnumFaninVisitor;
class PathEnumed;
class DiversionGreater;

typedef Vector<Diversion*> DiversionSeq;
typedef Vector<PathEnumed*> PathEnumedSeq;
typedef std::priority_queue<Diversion*,DiversionSeq,
			    DiversionGreater> DiversionQueue;

class DiversionGreater
{
public:
  DiversionGreater();
  DiversionGreater(const StaState *sta);
  bool operator()(Diversion *div1,
		  Diversion *div2) const;

private:
  const StaState *sta_;
};

// Iterator to enumerate sucessively slower paths.
class PathEnum : public Iterator<PathEnd*>, StaState
{
public:
  PathEnum(int group_count,
	   int endpoint_count,
	   bool unique_pins,
	   bool cmp_slack,
	   const StaState *sta);
  // Insert path ends that are enumerated in slack/arrival order.
  void insert(PathEnd *path_end);
  virtual ~PathEnum();
  virtual bool hasNext();
  virtual PathEnd *next();

private:
  void makeDiversions(PathEnd *path_end,
		      Path *before);
  void makeDiversion(PathEnd *div_end,
		     PathEnumed *after_div_copy);
  void makeDivertedPath(Path *path,
			Path *before_div,
			Path *after_div,
			TimingArc *div_arc,
			// Returned values.
			PathEnumed *&div_path,
			PathEnumed *&after_div_copy);
  void updatePathHeadDelays(PathEnumedSeq &path,
			    Path *after_div);
  Arrival divSlack(Path *path,
		   Path *after_div,
		   TimingArc *div_arc,
		   const PathAnalysisPt *path_ap);
  void reportDiversionPath(Diversion *div);
  void pruneDiversionQueue();
  Edge *divEdge(Path *before_div,
		TimingArc *div_arc);
  void findNext();

  bool cmp_slack_;
  int group_count_;
  int endpoint_count_;
  bool unique_pins_;
  DiversionQueue div_queue_;
  int div_count_;
  // Number of paths returned for each endpoint (limited to endpoint_count).
  VertexPathCountMap path_counts_;
  bool inserts_pruned_;
  PathEnd *next_;

  friend class PathEnumFaninVisitor;
};

} // namespace
