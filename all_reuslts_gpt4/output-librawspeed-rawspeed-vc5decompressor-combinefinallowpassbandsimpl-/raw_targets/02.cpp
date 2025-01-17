#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "rawspeed/api/RawImage.h"
#include "rawspeed/decompressors/VC5Decompressor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(rawspeed::VC5Decompressor::BandData)) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  rawspeed::VC5Decompressor::BandData bandData;
  provider.ConsumeData(&bandData, sizeof(bandData));

  rawspeed::VC5Decompressor decompressor(nullptr, nullptr);

  decompressor.combineFinalLowpassBandsImpl(&bandData);

  return 0;
}