#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str_ptr = reinterpret_cast<const char *>(data);
  std::string str{str_ptr, size};
  firebase::firestore::core::Query query;
  query.ParseFromString(str);

  size_t hash = query.Hash(&query);
  (void)hash;  // silence unused variable warning
  return 0;
}