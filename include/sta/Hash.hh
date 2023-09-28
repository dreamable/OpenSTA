



#include <cstdint>
#include <cstddef>

namespace sta {

using std::size_t;

const size_t hash_init_value = 5381;

// Dan Bernstein, comp.lang.c.
inline size_t
hashSum(size_t hash,
	size_t add)
{
  // hash * 31 ^ add.
  return ((hash << 5) + hash) ^ add;
}

inline void
hashIncr(size_t &hash,
	 size_t add)
{
  // hash * 31 ^ add.
  hash = ((hash << 5) + hash) ^ add;
}

inline size_t
nextMersenne(size_t n)
{
  return (n + 1) * 2 - 1;
}

// Sadly necessary until c++ std::hash works for char *.
size_t
hashString(const char *str);

// Pointer hashing is strongly discouraged because it causes results to change
// from run to run. Use Network::id functions instead.
#if __WORDSIZE == 64
  #define hashPtr(ptr) (reinterpret_cast<intptr_t>(ptr) >> 3)
#else
  #define hashPtr(ptr) (reinterpret_cast<intptr_t>(ptr) >> 2)
#endif

} // namespace
