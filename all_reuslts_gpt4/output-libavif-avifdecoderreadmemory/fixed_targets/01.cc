#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "avif/avif.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  avifDecoder *decoder = avifDecoderCreate();
  avifImage *image = avifImageCreateEmpty();

  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();
  avifResult result = avifDecoderReadMemory(decoder, image, buffer.data(), buffer.size());

  avifImageDestroy(image);
  avifDecoderDestroy(decoder);

  return 0;
}