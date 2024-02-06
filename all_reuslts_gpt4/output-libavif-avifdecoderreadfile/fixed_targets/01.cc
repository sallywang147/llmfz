#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "avif/avif.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  avifDecoder *decoder = avifDecoderCreate();
  avifImage *image = avifImageCreateEmpty();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *filename = const_cast<char*>(str.c_str());

  int result = avifDecoderReadFile(decoder, image, filename);

  avifDecoderDestroy(decoder);
  avifImageDestroy(image);

  return 0;
}