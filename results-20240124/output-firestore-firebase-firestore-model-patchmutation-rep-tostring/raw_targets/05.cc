 #include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/patch_mutation.h"

using firebase::firestore::model::FieldPath;
using firebase::firestore::model::PatchMutation;
using firebase::firestore::model::Value;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  PatchMutation::Rep rep;

  // Test PatchMutation::Rep::ToString(std::string, PatchMutation::Rep)
  try {
    std::string output;
    PatchMutation::Rep::ToString(&output, &rep);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test PatchMutation::Rep::FromString(std::string)
  try {
    PatchMutation::Rep::FromString(str);
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  // Test PatchMutation::Rep::FromFields(FieldPath, Value)
  try {
    PatchMutation::Rep::FromFields(FieldPath::FromString(str), Value::Null());
  } catch (...) {
    // Ignore caught errors and assertions.
  }

  return 0;
}