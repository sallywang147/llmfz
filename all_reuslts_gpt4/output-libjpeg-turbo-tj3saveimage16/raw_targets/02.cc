#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tj3SaveImage16.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int width = stream.ConsumeIntegralInRange<int>(1, 100);
  int height = stream.ConsumeIntegralInRange<int>(1, 100);
  int pitch = stream.ConsumeIntegralInRange<int>(width, width * 2);  // pitch should be equal or larger than width
  int pixelFormat = stream.ConsumeIntegral<int>();

  std::vector<short> buffer(width * height);
  char filename[] = "/tmp/fuzzed_image.tj3";
  char handle[] = "fuzzed_handle";

  // Call the function to fuzz
  tj3SaveImage16(handle, filename, buffer.data(), width, pitch, height, pixelFormat);

  return 0;
}