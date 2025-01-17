 #include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/query.h"
#include "Firestore/core/src/query_spec.h"

using firebase::firestore::core::Query;
using firebase::firestore::core::QuerySpec;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  QuerySpec query_spec = QuerySpec::FromFirestore(str);
  Query query(query_spec);
  query.Hash(&query);
  return 0;
}