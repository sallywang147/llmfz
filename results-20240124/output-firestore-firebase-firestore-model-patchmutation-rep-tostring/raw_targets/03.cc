 #include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/patch_mutation.h"

using firebase::firestore::model::PatchMutation;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  PatchMutation::Rep patch_mutation_rep;
  patch_mutation_rep.ToString(&str);

  return 0;
}