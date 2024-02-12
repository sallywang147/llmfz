#include <cstddef>
#include <cstdint>
#include <string>

#include "Firestore/core/src/model/document_key.h"
#include "Firestore/core/src/model/patch_mutation.h"

using firebase::firestore::model::PatchMutation;
using firebase::firestore::model::ResourcePath;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const char* str_ptr = reinterpret_cast<const char*>(data);
  std::string str{str_ptr, size};
  PatchMutation::ParseFromJson(str);

  std::string out;
  PatchMutation::ToString();

  return 0;
}