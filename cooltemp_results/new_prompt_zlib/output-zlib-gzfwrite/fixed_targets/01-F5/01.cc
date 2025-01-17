#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zlib.h"

extern "C" {
#include "zlib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gzFile file = gzdopen(0, "wb");
  if (file == nullptr) {
    return 0;
  }

  for (size_t i = 0; i < size; i++) {
    uint8_t value = stream.ConsumeIntegral<uint8_t>();
    size_t ret = gzfwrite(file, &value, sizeof(value), 1);
    if (ret == 0) {
      break;
    }
  }

  gzclose(file);
  return 0;
}