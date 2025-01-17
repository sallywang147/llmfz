 #include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/patch_mutation.h"
#include "Firestore/core/src/model/value.h"

using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::FieldValue;
using firebase::firestore::model::Mutation;
using firebase::firestore::model::PatchMutation;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  PatchMutation::Rep::ToString(&str, nullptr);
  return 0;
}