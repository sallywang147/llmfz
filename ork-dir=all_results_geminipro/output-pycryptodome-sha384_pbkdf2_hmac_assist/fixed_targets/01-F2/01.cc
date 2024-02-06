#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include "sha3/sha3.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 64) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);

  struct t_hash_state inner;
  struct t_hash_state outer;

  // Initialize the inner and outer hash states.
  SHA384_Init(&inner);
  SHA384_Init(&outer);

  // Generate a random first HMAC.
  uint8_t first_hmac[64];
  stream.ConsumeBytes(first_hmac, sizeof(first_hmac));

  // Generate a random result buffer.
  uint8_t result[64];
  stream.ConsumeBytes(result, sizeof(result));

  // Generate a random number of iterations.
  size_t iterations = stream.ConsumeIntegral<size_t>();

  // Generate a random digest size.
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  // Call the function under test.
  int ret = SHA384_pbkdf2_hmac_assist(&inner, &outer, (char *)first_hmac,
                                      (char *)result, iterations, digest_size);

  // Check the return value.
  if (ret != 0) {
    return 0;
  }

  return 0;
}