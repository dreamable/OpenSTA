

#include "StaState.hh"

#include <limits>

#include "DispatchQueue.hh"
#include "Units.hh"
#include "Network.hh"

namespace sta {

StaState::StaState() :
  report_(nullptr),
  debug_(nullptr),
  units_(nullptr),
  network_(nullptr),
  sdc_(nullptr),
  corners_(nullptr),
  graph_(nullptr),
  levelize_(nullptr),
  parasitics_(nullptr),
  arc_delay_calc_(nullptr),
  graph_delay_calc_(nullptr),
  sim_(nullptr),
  search_(nullptr),
  latches_(nullptr),
  clk_network_(nullptr),
  thread_count_(1),
  dispatch_queue_(nullptr),
  pocv_enabled_(false),
  sigma_factor_(1.0)
{
}

StaState::StaState(const StaState *sta)
{
  *this = *sta;
}

void
StaState::copyState(const StaState *sta)
{
  *this = *sta;
}

void
StaState::copyUnits(const Units *units)
{
  *units_ = *units;
}

NetworkEdit *
StaState::networkEdit()
{
  return dynamic_cast<NetworkEdit*>(network_);
}

NetworkEdit *
StaState::networkEdit() const
{
  return dynamic_cast<NetworkEdit*>(network_);
}

NetworkReader *
StaState::networkReader()
{
  return dynamic_cast<NetworkReader*>(network_);
}

NetworkReader *
StaState::networkReader() const
{
  return dynamic_cast<NetworkReader*>(network_);
}

void
StaState::setReport(Report *report)
{
  report_ = report;
}

void
StaState::setDebug(Debug *debug)
{
  debug_ = debug;
}

} // namespace
