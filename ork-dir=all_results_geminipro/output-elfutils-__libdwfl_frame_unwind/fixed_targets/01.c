#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libdwfl.h"

extern "C" {
#include "libdwfl.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(Dwfl_Frame)) {
    return 0;
  }
  Dwfl_Frame state;
  memcpy(&state, data, sizeof(state));
  libdwfl_frame_unwind(&state);  // Fixed the function name
  return 0;
}