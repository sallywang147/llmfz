#include <cstddef>
#include <cstdint>

#include "Firestore/core/src/core/query.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  firebase::firestore::core::Query query;
  size_t hash = query.Hash(&query);
  return 0;
}