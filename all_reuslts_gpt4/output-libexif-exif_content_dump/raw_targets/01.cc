#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libexif/exif-content.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ExifContent content;
  int indent = stream.ConsumeIntegral<int>();

  exif_content_dump(&content, indent);

  return 0;
}