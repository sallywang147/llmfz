#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zlib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t buffer_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> buffer(buffer_size);
  provider.ConsumeBytes(buffer.data(), buffer_size);

  gzFile file = gzdopen(0, "wb");
  if (file == nullptr) {
    return 0;
  }

  gzfwrite(buffer.data(), 1, buffer_size, file);
  gzclose(file);
  return 0;
}