



#include "NetworkClass.hh"
#include "NetworkCmp.hh"
#include "GraphClass.hh"

namespace sta {

class VertexNameLess
{
public:
  explicit VertexNameLess(Network *network);
  bool operator()(const Vertex *vertex1,
		  const Vertex *vertex2);

private:
  Network *network_;
};

class EdgeLess
{
public:
  EdgeLess(const Network *network,
	   Graph *graph);
  bool operator()(const Edge *edge1,
		  const Edge *edge2) const;

private:
  const PinPathNameLess pin_less_;
  Graph *graph_;
};

void
sortEdges(EdgeSeq *edges,
	  Network *network,
	  Graph *graph);

} // namespace
