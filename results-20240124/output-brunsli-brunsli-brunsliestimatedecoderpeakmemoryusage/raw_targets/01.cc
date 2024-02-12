 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "brunsli/brunsli_decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t data_size = stream.ConsumeIntegral<uint8_t>();
  char* data_ptr = new char[data_size];
  stream.ConsumeBytes(data_ptr, data_size);
  size_t result = brunsli::BrunsliEstimateDecoderPeakMemoryUsage(data_ptr,
                                                                data_size);
  delete[] data_ptr;
  return 0;
}