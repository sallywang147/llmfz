#include <fuzzer/FuzzedDataProvider.h>
#include "dss.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int size = stream.ConsumeIntegral<int>();

  // Call the function with the fuzzed arguments
  struct dropbear_DSS_Key* dssKey = gen_dss_priv_key(size);

  // Free the generated DSS key
  if (dssKey) {
    m_free(dssKey);
  }

  return 0;
}