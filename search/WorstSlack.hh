



#include <mutex>

#include "MinMax.hh"
#include "Vector.hh"
#include "GraphClass.hh"
#include "SearchClass.hh"
#include "StaState.hh"

namespace sta {

class StaState;
class WorstSlack;
class WnsSlackLess;

typedef Vector<WorstSlack> WorstSlackSeq;

class WorstSlacks
{
public:
  WorstSlacks(StaState *sta);
  void worstSlack(const MinMax *min_max,
		  // Return values.
		  Slack &worst_slack,
		  Vertex *&worst_vertex);
  void worstSlack(const Corner *corner,
		  const MinMax *min_max,
		  // Return values.
		  Slack &worst_slack,
		  Vertex *&worst_vertex);
  void updateWorstSlacks(Vertex *vertex,
			 SlackSeq &slacks);
  void worstSlackNotifyBefore(Vertex *vertex);

protected:
  WorstSlackSeq worst_slacks_;
  const StaState *sta_;
};

class WnsSlackLess
{
public:
  WnsSlackLess(PathAPIndex path_ap_index,
	       const StaState *sta);
  bool operator()(Vertex *vertex1,
		  Vertex *vertex2);

private:
  PathAPIndex path_ap_index_;
  Search *search_;
};

class WorstSlack : public StaState
{
public:
  WorstSlack(StaState *sta);
  ~WorstSlack();
  WorstSlack(const WorstSlack &);
  void worstSlack(PathAPIndex path_ap_index,
		  // Return values.
		  Slack &worst_slack,
		  Vertex *&worst_vertex);
  void updateWorstSlack(Vertex *vertex,
			SlackSeq &slacks,
			PathAPIndex path_ap_index);
  void deleteVertexBefore(Vertex *vertex);

protected:
  void findWorstSlack(PathAPIndex path_ap_index);
  void initQueue(PathAPIndex path_ap_index);
  void findWorstInQueue(PathAPIndex path_ap_index);
  void setWorstSlack(Vertex *vertex,
		     Slack slack);
  void sortQueue(PathAPIndex path_ap_index);
  void checkQueue(PathAPIndex path_ap_index);

  Slack slack_init_;
  // Vertex with the worst slack.
  // When nullptr the worst slack is unknown but in the queue.
  Vertex *worst_vertex_;
  Slack worst_slack_;
  Slack slack_threshold_;
  // Vertices with slack < threshold_
  VertexSet *queue_;
  // Queue is sorted and pruned to min_queue_size_ vertices when it
  // reaches max_queue_size_.
  int min_queue_size_;
  int max_queue_size_;
  std::mutex lock_;
};

} // namespace
