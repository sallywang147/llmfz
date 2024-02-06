#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document_comparator.h"

extern "C" {
#include "Firestore/core/src/api/fuzzer/fuzzed_data_provider.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  firebase::firestore::model::DocumentComparator comparator;
  firebase::firestore::core::Query query;
  query.SetComparator(&comparator);  // Corrected the function name

  return 0;
}