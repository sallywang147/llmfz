#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dropbear_dss.h"
#include "dropbear_ecdh.h"
#include "dropbear_ed25519.h"
#include "dropbear_key.h"
#include "dropbear_rsakey.h"
#include "dropbear_types.h"
#include "ssh.h"

extern "C" {
#include "dropbear_dss.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int key_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  struct dropbear_DSS_Key* key = gen_dss_priv_key(key_size);
  dropbear_dss_key_free(key);
  return 0;
}

extern "C" int gen_rsa_priv_key(int size) {
  FuzzedDataProvider stream(data, size);
  const int key_size = stream.ConsumeIntegralInRange<int>(0, 1024);
  struct dropbear_RSAKey* key = gen_rsa_priv_key(key_size);
  dropbear_rsa_key_free(key);
  return 0;
}