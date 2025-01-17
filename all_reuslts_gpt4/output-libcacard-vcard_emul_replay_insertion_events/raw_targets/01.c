#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "vcard_emul.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function vcard_emul_replay_insertion_events() does not take any arguments,
  // we don't need to use FuzzedDataProvider in this case.
  vcard_emul_replay_insertion_events();
  return 0;
}