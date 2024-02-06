#include <cstddef>
#include <cstdint>
#include <string>

extern "C" {
#include "Firestore/core/src/model/patch_mutation.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *str_ptr = reinterpret_cast<const char *>(data);
  std::string str{str_ptr, size};
  firebase::firestore::model::PatchMutation::Rep rep;
  std::string output;
  rep.ToString(&output);  // Add the address of output as the second parameter
  return 0;
}