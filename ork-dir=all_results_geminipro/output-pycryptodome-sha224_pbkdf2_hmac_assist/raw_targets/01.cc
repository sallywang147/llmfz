#include <fuzzer/FuzzedDataProvider.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sha224.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 32) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  struct t_hash_state inner, outer;
  uint8_t first_hmac[32];
  uint8_t result[32];
  uint8_t salt[32];
  stream.ConsumeBytes<uint8_t>(salt, sizeof(salt));
  SHA224_Init(&inner, salt);
  SHA224_Init(&outer, salt);
  SHA224_Update(&inner, &stream.ConsumeIntegral<uint8_t>(), 1);
  SHA224_Final(first_hmac, &inner);
  SHA224_Update(&outer, first_hmac, sizeof(first_hmac));
  size_t iterations = stream.ConsumeIntegralInRange<size_t>(0, 10000);
  size_t digest_size = stream.ConsumeIntegralInRange<size_t>(0, 32);
  SHA224_pbkdf2_hmac_assist(&inner, &outer, (char *)first_hmac, (char *)result,
                           iterations, digest_size);
  return 0;
}