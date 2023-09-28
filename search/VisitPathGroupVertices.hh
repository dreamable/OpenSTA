



namespace sta {

class PathGroup;
class VertexVisitor;
class StaState;

// Visit the fanin vertices for the path group.
// Vertices in the clock network are NOT visited.
void
visitPathGroupVertices(PathGroup *path_group,
		       VertexVisitor *visitor,
		       StaState *sta);

} // namespace
