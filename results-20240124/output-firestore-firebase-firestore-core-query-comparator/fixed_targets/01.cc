#include <cstddef>
#include <cstdint>

#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document_comparator.h"

extern "C" {
#include "Firestore/core/src/model/document_comparator.h"
}

using firebase::firestore::core::Query;
using firebase::firestore::model::DocumentComparator;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  DocumentComparator comparator;
  Query query;
  query.Comparator(&comparator, &query);
  return 0;
}