 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <vector>

#include "zlib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  gzFile file = gzdopen(0, "w");
  if (file == nullptr) {
    return 0;
  }

  for (size_t i = 0; i < size; i++) {
    int c = stream.ConsumeIntegral<int>();
    int ret = gzputc(file, c);
    if (ret == EOF) {
      break;
    }
  }

  gzclose(file);
  return 0;
}