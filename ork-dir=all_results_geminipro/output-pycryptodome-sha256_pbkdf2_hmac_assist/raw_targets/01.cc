#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "sha256.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 32) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create the inner and outer hash states.
  struct t_hash_state inner;
  struct t_hash_state outer;
  SHA256_init(&inner);
  SHA256_init(&outer);

  // Consume the first 32 bytes as the password.
  std::vector<uint8_t> password = stream.ConsumeBytes<uint8_t>(32);

  // Consume the next 16 bytes as the salt.
  std::vector<uint8_t> salt = stream.ConsumeBytes<uint8_t>(16);

  // Consume the next 4 bytes as the number of iterations.
  uint32_t iterations = stream.ConsumeIntegral<uint32_t>();

  // Consume the next 4 bytes as the digest size.
  uint32_t digest_size = stream.ConsumeIntegral<uint32_t>();

  // Consume the remaining bytes as the first HMAC.
  std::vector<uint8_t> first_hmac = stream.ConsumeRemainingBytes();

  // Allocate a buffer for the result.
  char result[digest_size];

  // Call the function to be fuzzed.
  int ret = SHA256_pbkdf2_hmac_assist(&inner, &outer, (char *)first_hmac.data(),
                                      result, iterations, digest_size);

  // Check the return value.
  if (ret != 0) {
    return 0;
  }

  // Consume the remaining bytes as the expected result.
  std::vector<uint8_t> expected_result = stream.ConsumeRemainingBytes();

  // Compare the result with the expected result.
  if (memcmp(result, expected_result.data(), digest_size) != 0) {
    return 0;
  }

  return 0;
}