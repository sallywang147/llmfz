#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "vcard_emul.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // The function does not take any parameters, so we do not need to generate any inputs.
  vcard_emul_replay_insertion_events();

  return 0;
}