#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct t_hash_state inner;
  struct t_hash_state outer;
  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  // Ensure we have enough data for first_hmac and result
  if (stream.remaining_bytes() < 2 * digest_size) {
    return 0;
  }

  std::vector<char> first_hmac = stream.ConsumeBytes<char>(digest_size);
  std::vector<char> result(digest_size);

  SHA384_pbkdf2_hmac_assist(&inner, &outer, first_hmac.data(), result.data(), iterations, digest_size);

  return 0;
}