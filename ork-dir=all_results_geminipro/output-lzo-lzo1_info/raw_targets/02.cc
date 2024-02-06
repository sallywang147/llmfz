#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "lzo/lzoconf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int rbits = stream.ConsumeIntegral<int>();
  int clevel = stream.ConsumeIntegral<int>();
  size_t ret = lzo1_info(&rbits, &clevel);
  return 0;
}