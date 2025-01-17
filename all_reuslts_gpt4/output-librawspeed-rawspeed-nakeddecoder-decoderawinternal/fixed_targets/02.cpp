#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "rawspeed_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  rawspeed::RawImage rawImage;
  rawspeed::NakedDecoder nakedDecoder;

  // Initialize rawImage and nakedDecoder with fuzzed data
  // ...

  // Call the function to fuzz
  rawspeed::NakedDecoder::decodeRawInternal(&rawImage, &nakedDecoder);

  return 0;
}