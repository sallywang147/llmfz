#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "firebase/firestore/core/query.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a Query object
  firebase::firestore::core::Query query;

  // Use the fuzzed data to create another Query object
  firebase::firestore::core::Query fuzzed_query;

  // Call the Hash function
  size_t hash = query.Hash(&fuzzed_query);

  return 0;
}