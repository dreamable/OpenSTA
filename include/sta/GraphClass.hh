



#include <limits>

#include "ObjectId.hh"
#include "Set.hh"
#include "Vector.hh"
#include "MinMax.hh"
#include "Transition.hh"

namespace sta {

// Class declarations for pointer references.
class Graph;
class Vertex;
class Edge;
class VertexIterator;
class VertexInEdgeIterator;
class VertexOutEdgeIterator;
class GraphLoop;
class VertexSet;

typedef ObjectId VertexId;
typedef ObjectId EdgeId;
typedef ObjectId ArcId;
typedef Vector<Vertex*> VertexSeq;
typedef Vector<Edge*> EdgeSeq;
typedef Set<Edge*> EdgeSet;
typedef int Level;
typedef int DcalcAPIndex;
typedef int TagGroupIndex;
typedef Vector<GraphLoop*> GraphLoopSeq;

static constexpr int level_max = std::numeric_limits<Level>::max();

// 16,777,215 tags
static const int tag_group_index_bits = 24;
static const TagGroupIndex tag_group_index_max = (1<<tag_group_index_bits)-1;
static const int slew_annotated_bits = MinMax::index_count * RiseFall::index_count;

// Bit shifts used to mark vertices in a Bfs queue.
enum class BfsIndex { dcalc, arrival, required, other, bits };

} // namespace
