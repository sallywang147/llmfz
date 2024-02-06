#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libraw/libraw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;  // Not enough data to do anything.
  }

  FuzzedDataProvider stream(data, size);

  // Define and initialize parameters
  LibRaw rawProcessor;
  int planeNumber = stream.ConsumeIntegral<int>();
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *p = const_cast<char*>(str.c_str());

  // Call the target function
  rawProcessor.crxDecodePlane(p, planeNumber);

  return 0;
}