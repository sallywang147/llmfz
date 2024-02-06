#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dss.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int key_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  struct dropbear_DSS_Key* key = gen_dss_priv_key(key_size);
  dropbear_dss_key_free(key);
  return 0;
}