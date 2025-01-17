#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avif/avif.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  avifDecoder * decoder = avifDecoderCreate();
  if (!decoder)
    return 0;

  avifImage * image = avifImageCreateEmpty();
  if (!image) {
    avifDecoderDestroy(decoder);
    return 0;
  }

  size_t dataSize = stream.remaining_bytes();
  std::vector<char> avifData = stream.ConsumeBytes<char>(dataSize);
  avifResult result = avifDecoderReadMemory(decoder, image, avifData.data(), dataSize);

  avifImageDestroy(image);
  avifDecoderDestroy(decoder);

  return 0;
}