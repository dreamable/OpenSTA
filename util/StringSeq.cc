

#include "StringSeq.hh"

namespace sta {

void
deleteContents(StringSeq *strings)
{
  StringSeq::Iterator iter(strings);
  while (iter.hasNext()) {
    const char *string = iter.next();
    stringDelete(string);
  }
}

} // namespace
