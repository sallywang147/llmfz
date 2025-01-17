#include "fuzz.h"
#include "fuzz-wrapfd.h"
#include "dss.h"
#include "buffer.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int key_size = stream.ConsumeIntegralInRange<int>(512, 1024);
  struct dropbear_DSS_Key *dss_key = gen_dss_priv_key(key_size);

  if (dss_key != nullptr) {
    m_free(dss_key);
  }

  return 0;
}