#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Assuming struct t_hash_state has a size of 64 bytes. Adjust according to actual size.
  struct t_hash_state inner;
  struct t_hash_state outer;
  stream.ConsumeData(&inner, sizeof(inner));
  stream.ConsumeData(&outer, sizeof(outer));

  // Consume data for first_hmac and result with a size of 32 bytes each. Adjust according to actual size.
  std::vector<char> first_hmac = stream.ConsumeBytes<char>(32);
  std::vector<char> result = stream.ConsumeBytes<char>(32);

  // Consume data for iterations and digest_size.
  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  // Call the function under test.
  SHA256_pbkdf2_hmac_assist(&inner, &outer, first_hmac.data(), result.data(), iterations, digest_size);

  return 0;
}