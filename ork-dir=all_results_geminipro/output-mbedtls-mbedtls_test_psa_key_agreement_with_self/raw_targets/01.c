#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "mbedtls/psa.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  psa_key_derivation_s operation = {};
  const int key = stream.ConsumeIntegral<int>();
  mbedtls_test_psa_key_agreement_with_self(&operation, key);
  return 0;
}