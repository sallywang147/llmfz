#include <cstddef>
#include <cstdint>

extern "C" {
#include "Firestore/core/src/core/query.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  firebase::firestore::core::Query query;
  size_t hash = query.Hash();  // Fix: Remove the &query parameter.
  return 0;
}