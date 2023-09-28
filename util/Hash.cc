

#include "Hash.hh"

#include <cstring>

namespace sta {

size_t
hashString(const char *str)
{
  size_t hash = hash_init_value;
  size_t length = strlen(str);
  for (size_t i = 0; i < length; i++)
    hash = ((hash << 5) + hash) ^ str[i];
  return hash;
}

} // namespace
