#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "lzo2a_999.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct lzo2a_999_swd_t s;
  const size_t node = stream.ConsumeIntegral<size_t>();
  const size_t len = stream.ConsumeIntegral<size_t>();
  swd_init(&s); // Initialize the sliding window data structure
  swd_insertdict(&s, node, len);
  return 0;
}