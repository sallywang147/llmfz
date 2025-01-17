#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "gd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  FILE* file = fmemopen(bytes.data(), bytes.size(), "rb");
  if (file == nullptr) {
    return 0;
  }
  gdImagePtr image = gdImageCreateFromBmp(file);
  if (image == nullptr) {
    fclose(file);
    return 0;
  }
  gdImageDestroy(image);
  fclose(file);
  return 0;
}