#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document_comparator.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  firebase::firestore::model::DocumentComparator comparator;
  firebase::firestore::core::Query query;
  query.Comparator(&comparator);
  return 0;
}