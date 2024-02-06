#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "rawspeed/api/RawImage.h"
#include "rawspeed/common/Buffer.h"
#include "rawspeed/decompressors/VC5Decompressor.h"

using namespace rawspeed;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(VC5Decompressor))
    return 0;

  FuzzedDataProvider provider(data, size);

  // Create a VC5Decompressor object from the fuzzed data.
  VC5Decompressor decompressor1(provider.ConsumeBytes<uint8_t>(sizeof(VC5Decompressor)).data());

  // Create another VC5Decompressor object from the remaining fuzzed data.
  VC5Decompressor decompressor2(provider.ConsumeRemainingBytes<uint8_t>().data());

  // Call the target function.
  decompressor1.combineFinalLowpassBands(&decompressor2);

  return 0;
}