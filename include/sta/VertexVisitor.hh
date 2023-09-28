



#include "NetworkClass.hh"
#include "GraphClass.hh"

namespace sta {

// Abstract base class for visiting a vertex.
class VertexVisitor
{
public:
  VertexVisitor() {}
  virtual ~VertexVisitor() {}
  virtual VertexVisitor *copy() const = 0;
  virtual void visit(Vertex *vertex) = 0;
  void operator()(Vertex *vertex) { visit(vertex); }
  virtual void levelFinished() {}
};

// Collect visited pins into a PinSet.
class VertexPinCollector : public VertexVisitor
{
public:
  VertexPinCollector(PinSet &pins);
  const PinSet &pins() const { return pins_; }
  void visit(Vertex *vertex);
  virtual VertexVisitor *copy() const;

protected:
  PinSet &pins_;
};

} // namespace
