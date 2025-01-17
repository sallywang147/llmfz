#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/field_value.h"
#include "Firestore/core/src/model/patch_mutation.h"
#include "Firestore/core/src/model/value_util.h"

extern "C" {
#include "Firestore/core/src/util/status.h"
}

using firebase::firestore::model::FieldValue;
using firebase::firestore::model::PatchMutation;
using firebase::firestore::util::Status;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};

  PatchMutation::Rep rep(PatchMutation::kPatchMutationTypeUpdateData,
                         FieldValue::FromData(str));
  std::string output;
  Status status = rep.ToString(&output);
  if (!status.ok()) {
    return 1;
  }

  return 0;
}