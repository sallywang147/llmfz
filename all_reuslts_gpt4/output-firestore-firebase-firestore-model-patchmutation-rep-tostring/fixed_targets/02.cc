#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "firebase/firestore/model/patch_mutation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRandomLengthString();
  firebase::firestore::model::PatchMutation::Rep patchMutationRep;

  patchMutationRep.ToString(&str, &patchMutationRep);

  return 0;
}