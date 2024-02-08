#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "psa/crypto.h"
#include "psa/crypto_derivation.h"
#include "psa/crypto_key_agreement.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct psa_key_derivation_s operation;
  memset(&operation, 0, sizeof(operation));

  operation.alg = stream.ConsumeIntegralInRange<psa_algorithm_t>(
      PSA_ALG_HKDF_SHA_256, PSA_ALG_HKDF_SHA_512);
  operation.key = stream.ConsumeIntegralInRange<psa_key_id_t>(1, 1000);
  operation.output = stream.ConsumeIntegralInRange<psa_key_id_t>(1, 1000);

  int key = stream.ConsumeIntegralInRange<int>(1, 1000);

  mbedtls_test_psa_key_agreement_with_self(&operation, key);

  return 0;
}