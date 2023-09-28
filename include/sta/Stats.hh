



#include <cstddef>  // size_t

namespace sta {

class Debug;
class Report;

// Show run time and memory statistics if the "stats" debug flag is on.
class Stats
{
public:
  explicit Stats(Debug *debug,
                 Report *report);
  void report(const char *step);

private:
  double elapsed_begin_;
  double user_begin_;
  double system_begin_;
  size_t memory_begin_;
  Debug *debug_;
  Report *report_;
};

} // namespace
