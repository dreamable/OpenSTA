

#include "VertexVisitor.hh"

#include "Error.hh"
#include "Graph.hh"

namespace sta {

VertexPinCollector::VertexPinCollector(PinSet &pins) :
  pins_(pins)
{
}

VertexVisitor *
VertexPinCollector::copy() const
{
  criticalError(266, "VertexPinCollector::copy not supported.");
  return nullptr;
}

void
VertexPinCollector::visit(Vertex *vertex)
{
  pins_.insert(vertex->pin());
}

} // namespace
