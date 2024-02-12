#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/document_comparator.h"
#include "Firestore/core/src/query/query.h"

using firebase::firestore::core::Query;
using firebase::firestore::model::DocumentComparator;

extern "C" {
#include "Firestore/core/src/util/hard_assert.h"
#include "Firestore/core/src/model/document_comparator.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  DocumentComparator doc_comparator;
  Query query;
  query.Comparator(&doc_comparator, &query);
  return 0;
}