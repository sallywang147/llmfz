#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rawspeed/api/RawImage.h"
#include "rawspeed/decompressors/VC5Decompressor.h"

using namespace rawspeed;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Initialize a VC5Decompressor object
  VC5Decompressor vc5;

  // Initialize another VC5Decompressor object to pass as an argument to the function
  VC5Decompressor vc5_arg;

  // Call the function
  vc5.combineFinalLowpassBands(&vc5_arg);

  return 0;
}