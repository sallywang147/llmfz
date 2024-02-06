#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "lzo2a_999.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t node = stream.ConsumeIntegral<size_t>();
  const size_t len = stream.ConsumeIntegral<size_t>();
  lzo2a_999_swd_t* s = new lzo2a_999_swd_t();
  swd_insertdict(s, node, len);
  delete s;
  return 0;
}