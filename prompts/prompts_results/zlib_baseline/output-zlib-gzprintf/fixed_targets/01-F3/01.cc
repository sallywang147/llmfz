#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "zlib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::vector<uint8_t> buffer(provider.ConsumeBytes<uint8_t>(size));

  gzFile file = gzdopen(0, "wb");
  if (file == nullptr) {
    return 0;
  }

  gzprintf(file, "%s", buffer.data());
  gzclose(file);

  return 0;
}