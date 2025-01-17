#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "libraw/libraw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize LibRaw instance
  LibRaw RawProcessor;

  // Consume data for planeNumber
  int planeNumber = stream.ConsumeIntegral<int>();

  // Consume remaining bytes as string for p
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *p = const_cast<char *>(str.c_str());

  // Call the target function
  RawProcessor.crxDecodePlane(p, planeNumber);

  return 0;
}