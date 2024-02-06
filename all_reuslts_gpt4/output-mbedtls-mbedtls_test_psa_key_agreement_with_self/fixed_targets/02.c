#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "psa/crypto.h"
#include "mbedtls_test.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the PSA Crypto subsystem
  psa_status_t status = psa_crypto_init();
  if (status != PSA_SUCCESS) {
    return 0;
  }

  // Initialize a key derivation operation
  psa_key_derivation_operation_t operation = PSA_KEY_DERIVATION_OPERATION_INIT;

  // Consume data from the fuzzer input
  int key = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  int ret = mbedtls_test_psa_key_agreement_with_self(&operation, key);

  // Clean up and return
  psa_key_derivation_abort(&operation);
  return 0;
}