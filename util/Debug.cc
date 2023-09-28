

#include "Debug.hh"

#include "Report.hh"

namespace sta {

bool debug_on = false;

Debug::Debug(Report *report) :
  report_(report),
  debug_on_(false),
  debug_map_(nullptr),
  stats_level_(0)
{
}

Debug::~Debug()
{
  if (debug_map_) {
    DebugMap::Iterator debug_iter(debug_map_);
    // Delete the debug map keys.
    while (debug_iter.hasNext()) {
      const char *what;
      int level;
      debug_iter.next(what, level);
      delete [] what;
    }
    delete debug_map_;
  }
}

bool
Debug::check(const char *what,
	     int level) const
{
  if (debug_on_
      && debug_map_) {
    int dbg_level;
    bool exists;
    debug_map_->findKey(what, dbg_level, exists);
    if (exists)
      return dbg_level >= level;
  }
  return false;
}

int
Debug::level(const char *what)
{
  if (debug_map_) {
    const char *key;
    int dbg_level;
    bool exists;
    debug_map_->findKey(what, key, dbg_level, exists);
    if (exists)
      return dbg_level;
  }
  return 0;
}

void
Debug::setLevel(const char *what,
		int level)
{
  if (stringEq(what, "stats"))
    stats_level_ = level;
  else if (level == 0) {
    if (debug_map_) {
      int dbg_level;
      bool exists;
      const char *key;
      debug_map_->findKey(what, key, dbg_level, exists);
      if (exists) {
	debug_map_->erase(what);
	delete [] key;
      }
      debug_on_ = !debug_map_->empty();
    }
  }
  else {
    char *what_cpy = new char[strlen(what) + 1];
    strcpy(what_cpy, what);
    if (debug_map_ == nullptr)
      debug_map_ = new DebugMap;
    (*debug_map_)[what_cpy] = level;
    debug_on_ = true;
  }
}

void
Debug::reportLine(const char *what,
                  const char *fmt,
                  ...) const
{
  va_list args;
  va_start(args, fmt);
  report_->printToBuffer("%s", what);
  report_->printToBufferAppend(": ");
  report_->printToBufferAppend(fmt, args);
  report_->printBufferLine();
  va_end(args);
}

} // namespace
