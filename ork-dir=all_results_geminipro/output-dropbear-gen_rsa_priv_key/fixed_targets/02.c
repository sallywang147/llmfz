#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dropbear.h"
#include "dss.h"
#include "ssh.h"

extern "C" {
#include "libssh2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int key_size = stream.ConsumeIntegralInRange<int>(256, 4096);
  const struct dropbear_DSS_Key* key = gen_dss_priv_key(key_size);  // Fix typo here
  dropbear_dss_key_free(key);
  return 0;
}