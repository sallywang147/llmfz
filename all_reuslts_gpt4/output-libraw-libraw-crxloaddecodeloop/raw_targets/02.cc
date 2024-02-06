#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libraw/libraw.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create a LibRaw instance
  LibRaw rawProcessor;
  
  // Extract the number of planes
  int nPlanes = stream.ConsumeIntegral<int>();
  
  // Extract the image data
  std::string img = stream.ConsumeRemainingBytesAsString();
  
  // Call the function under test
  rawProcessor.crxLoadDecodeLoop(&rawProcessor, img.data(), nPlanes);
  
  return 0;
}