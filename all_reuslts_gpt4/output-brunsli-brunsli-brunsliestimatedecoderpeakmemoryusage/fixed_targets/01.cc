#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "brunsli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data as a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* input_data = const_cast<char*>(str.c_str());

  // Call the target function
  size_t peak_memory_usage = brunsli::BrunsliEstimateDecoderPeakMemoryUsage(input_data, size);

  return 0;
}