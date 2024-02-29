 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zlib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  gzFile file = gzdopen(0, "wb");
  if (file == nullptr) {
    return 0;
  }

  size_t num_iterations = provider.ConsumeIntegralInRange<size_t>(0, 100);
  for (size_t i = 0; i < num_iterations; i++) {
    size_t num_bytes = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    auto bytes = provider.ConsumeBytes<uint8_t>(num_bytes);
    gzfwrite(bytes.data(), 1, num_bytes, file);
  }

  gzclose(file);
  return 0;
}