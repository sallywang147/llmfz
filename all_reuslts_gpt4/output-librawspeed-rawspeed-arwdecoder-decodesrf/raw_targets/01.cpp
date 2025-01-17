#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "rawspeed/api/RawImage.h"
#include "rawspeed/api/RawImageData.h"
#include "rawspeed/decoders/ArwDecoder.h"

using namespace rawspeed;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(RawImage)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Extract RawImage object from the stream
  RawImage rawImage;
  size_t consumed = stream.ConsumeData(&rawImage, sizeof(rawImage));
  if (consumed != sizeof(rawImage)) {
    return 0;
  }

  // Create ArwDecoder object
  ArwDecoder arwDecoder;

  // Call the function to fuzz
  arwDecoder.decodeSRF(&rawImage, &arwDecoder);

  return 0;
}