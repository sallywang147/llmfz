#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "Firestore/core/src/model/document_comparator.h"
#include "Firestore/core/src/query/query.h"
}

using firebase::firestore::core::Query;
using firebase::firestore::model::DocumentComparator;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const std::string data_str(reinterpret_cast<const char *>(data), size);
  DocumentComparator comparator;
  Query query;
  query.SetComparator(&comparator);  // Fix: Use SetComparator instead of Comparator
  return 0;
}