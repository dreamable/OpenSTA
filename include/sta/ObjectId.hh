



#include <cstdint>

namespace sta {

// ObjectId is block index and object index within the block.
typedef uint32_t ObjectId;
// Block index.
typedef uint32_t BlockIdx;
// Object index within a block.
typedef uint32_t ObjectIdx;

static constexpr int object_id_bits = sizeof(ObjectId) * 8;
static constexpr BlockIdx block_idx_null = 0;
static constexpr ObjectId object_id_null = 0;
static constexpr ObjectIdx object_idx_null = 0;

} // Namespace
