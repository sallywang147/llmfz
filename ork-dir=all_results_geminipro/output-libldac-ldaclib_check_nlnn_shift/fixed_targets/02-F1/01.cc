#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
extern "C" {
#include "ldaclib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int smplrate_id = stream.ConsumeIntegral<int>();
  const int nlnn_shift = stream.ConsumeIntegral<int>();
  ldaclib_check_nlnn_shift(smplrate_id, nlnn_shift);
  return 0;
}