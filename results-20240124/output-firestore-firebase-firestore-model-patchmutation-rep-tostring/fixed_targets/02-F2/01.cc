#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/patch_mutation.h"
#include "Firestore/core/src/model/value_util.h"

using firebase::firestore::model::FieldValue;
using firebase::firestore::model::PatchMutation;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  PatchMutation::Rep rep(PatchMutation::PatchMutationType::UpdateData,
                         FieldValue::FromData(str));
  std::string output;
  rep.ToString(&output);

  return 0;
}