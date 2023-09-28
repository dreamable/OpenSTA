



#include <cstdarg>

#include "Map.hh"
#include "StringUtil.hh"

namespace sta {

class Report;
class Pin;

typedef Map<const char *, int, CharPtrLess> DebugMap;

class Debug
{
public:
  explicit Debug(Report *report);
  ~Debug();
  int level(const char *what);
  void setLevel(const char *what,
		int level);
  bool check(const char *what,
	     int level) const;
  int statsLevel() const { return stats_level_; }
  void reportLine(const char *what,
                  const char *fmt,
                  ...) const
    __attribute__((format (printf, 3, 4)));

protected:
  Report *report_;
  bool debug_on_;
  DebugMap *debug_map_;
  int stats_level_;
};

// Inlining a varargs function would eval the args, which can
// be expensive, so use a macro.
// Note that "##__VA_ARGS__" is a gcc extension to support zero arguments (no comma).
// clang -Wno-gnu-zero-variadic-macro-arguments suppresses the warning.
// c++20 has "__VA_OPT__" to deal with the zero arg case so this is temporary.
#define debugPrint(debug, what, level, ...) \
  if (debug->check(what, level)) {  \
    debug->reportLine(what, ##__VA_ARGS__); \
  }

} // namespace
