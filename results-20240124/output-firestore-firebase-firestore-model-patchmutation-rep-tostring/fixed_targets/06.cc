#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/patch_mutation.h"

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  firebase::firestore::model::PatchMutation::Rep rep;
  rep.FromString(str);

  std::string output;
  rep.ToString(&output);

  return 0;
}
}