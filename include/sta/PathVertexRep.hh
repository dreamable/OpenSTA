



#include "SdcClass.hh"
#include "SearchClass.hh"

namespace sta {

// Path representation that references a vertex arrival via a tag.
// This does not implement the Path API which uses virtual functions
// that would make it larger.
class PathVertexRep
{
public:
  explicit PathVertexRep();
  explicit PathVertexRep(const PathVertexRep *path);
  PathVertexRep(const PathVertexRep &path);
  explicit PathVertexRep(const PathVertex *path,
			 const StaState *sta);
  explicit PathVertexRep(const PathVertex &path,
			 const StaState *sta);
  explicit PathVertexRep(VertexId vertex_id,
			 TagIndex tag_index,
			 bool is_enum);
  void init();
  void init(const PathVertexRep *path);
  void init(const PathVertexRep &path);
  void init(const PathVertex *path,
	    const StaState *sta);
  void init(const PathVertex &path,
	    const StaState *sta);
  bool isNull() const { return vertex_id_ == 0; }
  Vertex *vertex(const StaState *) const;
  VertexId vertexId() const { return vertex_id_; }
  Tag *tag(const StaState *sta) const;
  TagIndex tagIndex() const { return tag_index_; }
  Arrival arrival(const StaState *sta) const;
  void prevPath(const StaState *sta,
		// Return values.
		PathRef &prev_path,
		TimingArc *&prev_arc) const;

  static bool equal(const PathVertexRep *path1,
		    const PathVertexRep *path2);
  static bool equal(const PathVertexRep &path1,
		    const PathVertexRep &path2);
  static int cmp(const PathVertexRep *path1,
		 const PathVertexRep *path2);
  static int cmp(const PathVertexRep &path1,
		 const PathVertexRep &path2);

protected:
  VertexId vertex_id_;
  TagIndex tag_index_;
  bool is_enum_:1;
};

} // namespace
