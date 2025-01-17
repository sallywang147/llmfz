 #include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/patch_mutation.h"

using firebase::firestore::model::PatchMutation;
using firebase::firestore::model::PatchMutation::Rep;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  Rep rep;
  rep.field_path_ = ResourcePath::FromString(str);

  std::string out;
  rep.ToString(&out, &rep);

  return 0;
}