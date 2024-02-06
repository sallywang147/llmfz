#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/core/query.h"

extern "C" {
#include "Firestore/core/src/util/hashing.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str_ptr = reinterpret_cast<const char *>(data);
  std::string str{str_ptr, size};
  firebase::firestore::core::Query query;
  query.ParseFromString(str);

  size_t hash = firebase::firestore::core::util::Hash(&query);
  (void)hash;  // silence unused variable warning
  return 0;
}