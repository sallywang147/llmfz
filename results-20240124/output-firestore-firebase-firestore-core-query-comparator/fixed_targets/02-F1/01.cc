#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "Firestore/core/src/core/query.h"
#include "Firestore/core/src/model/document_comparator.h"
#include "Firestore/core/src/model/resource_path.h"
}

using firebase::firestore::core::Query;
using firebase::firestore::model::DocumentComparator;
using firebase::firestore::model::ResourcePath;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  ResourcePath rp = ResourcePath::FromString(str);
  Query query(rp);
  DocumentComparator comparator;
  query.Comparator(&comparator, &query);
  return 0;
}