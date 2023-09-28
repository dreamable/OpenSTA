



#include "StringUtil.hh"
#include "Set.hh"

namespace sta {

typedef Set<const char*, CharPtrLess> StringSet;

void
deleteContents(StringSet *strings);

} // namespace
