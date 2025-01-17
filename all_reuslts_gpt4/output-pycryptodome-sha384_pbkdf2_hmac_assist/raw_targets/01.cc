#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;  // Not enough data to do anything.
  }

  FuzzedDataProvider provider(data, size);

  // Create hash state objects.
  struct t_hash_state inner;
  struct t_hash_state outer;

  // Initialize hash state objects.
  hash_init(&inner);
  hash_init(&outer);

  // Prepare first_hmac and result buffers.
  const size_t digest_size = provider.ConsumeIntegralInRange<size_t>(1, size / 2);
  std::vector<char> first_hmac = provider.ConsumeBytes<char>(digest_size);
  std::vector<char> result(digest_size);

  // Consume remaining data for iterations.
  size_t iterations = provider.ConsumeIntegral<size_t>();

  // Call the target function.
  SHA384_pbkdf2_hmac_assist(&inner, &outer, first_hmac.data(), result.data(), iterations, digest_size);

  return 0;
}