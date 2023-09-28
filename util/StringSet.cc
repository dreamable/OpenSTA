

#include "StringSet.hh"

namespace sta {

void
deleteContents(StringSet *strings)
{
  StringSet::Iterator iter(strings);
  while (iter.hasNext()) {
    const char *string = iter.next();
    stringDelete(string);
  }
}

} // namespace
