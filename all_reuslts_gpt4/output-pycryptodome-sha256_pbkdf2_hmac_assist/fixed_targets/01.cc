#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct t_hash_state inner;
  struct t_hash_state outer;

  // Initialize the hash states
  hash_init(&inner);
  hash_init(&outer);

  // Consume data for first_hmac
  size_t first_hmac_size = stream.ConsumeIntegralInRange<size_t>(1, size / 2);
  std::string first_hmac = stream.ConsumeBytesAsString(first_hmac_size);

  // Consume data for result
  size_t result_size = stream.ConsumeIntegralInRange<size_t>(1, size / 2);
  std::vector<char> result(result_size);

  // Consume data for iterations and digest_size
  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  // Call the function to be fuzzed
  SHA256_pbkdf2_hmac_assist(&inner, &outer, (char*)first_hmac.c_str(), result.data(), iterations, digest_size);

  return 0;
}