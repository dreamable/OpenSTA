

#include "Stats.hh"

#include "Machine.hh"
#include "StringUtil.hh"
#include "Report.hh"
#include "Debug.hh"

namespace sta {

Stats::Stats(Debug *debug,
             Report *report) :
  elapsed_begin_(0.0),
  user_begin_(0.0),
  system_begin_(0.0),
  memory_begin_(0),
  debug_(debug),
  report_(report)
{
  if (debug->statsLevel() > 0) {
    elapsed_begin_ = elapsedRunTime();
    user_begin_ = userRunTime();
    system_begin_ = systemRunTime();
    memory_begin_ = memoryUsage();
  }
}

void
Stats::report(const char *step)
{
  if (debug_->statsLevel() > 0) {
    double elapsed_end = elapsedRunTime();
    double user_end = userRunTime();
    double memory_begin = static_cast<double>(memory_begin_);
    double memory_end = static_cast<double>(memoryUsage());
    double memory_delta = memory_end - memory_begin;
    report_->reportLine("stats: %5.1f/%5.1fe %5.1f/%5.1fu %5.1f/%5.1fMB %s",
                        elapsed_end - elapsed_begin_, elapsed_end,
                        user_end - user_begin_, user_end,
                        memory_delta * 1e-6, memory_end * 1e-6,
                        step);
  }
}

} // namespace
