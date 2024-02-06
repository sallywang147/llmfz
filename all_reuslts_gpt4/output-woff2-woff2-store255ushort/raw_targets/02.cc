#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

#include "woff2/encode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int val = stream.ConsumeIntegral<int>();
  size_t offset = stream.ConsumeIntegral<size_t>();
  std::string dst = stream.ConsumeRemainingBytesAsString();

  if (offset > dst.size()) {
    return 0;
  }

  woff2::Store255UShort(val, &offset, &dst[0]);

  return 0;
}