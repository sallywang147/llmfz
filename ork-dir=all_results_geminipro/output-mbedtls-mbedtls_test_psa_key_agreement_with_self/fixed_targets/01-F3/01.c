#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "mbedtls/psa.h"
#include "mbedtls/psa_crypto.h"  // Include the header for mbedtls_psa_key_agreement_with_self

extern "C" {
#include "mbedtls/psa_crypto_derivation.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  psa_key_derivation_s operation = {};
  const int key = stream.ConsumeIntegral<int>();
  mbedtls_psa_key_agreement_with_self(&operation, key);
  return 0;
}

int mbedtls_test_psa_key_agreement_with_self(psa_key_derivation_s * operation, int key) {
  return 0;
}