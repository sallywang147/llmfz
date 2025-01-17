#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "firebase/firestore/model/patch_mutation.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string output;
  firebase::firestore::model::PatchMutation::Rep mutation_rep;

  // The function is const, so we need to create a const reference to call it
  const firebase::firestore::model::PatchMutation::Rep& const_mutation_rep = mutation_rep;

  const_mutation_rep.ToString(&output, &mutation_rep);

  return 0;
}