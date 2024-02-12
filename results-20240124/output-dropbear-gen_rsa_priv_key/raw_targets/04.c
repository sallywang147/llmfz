 #include <fuzzer/FuzzedDataProvider.h>

#include "dropbear.h"
#include "dss.h"
#include "ssh.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int key_size = stream.ConsumeIntegralInRange<int>(1, 1024);
  gen_rsa_priv_key(key_size);
  return 0;
}