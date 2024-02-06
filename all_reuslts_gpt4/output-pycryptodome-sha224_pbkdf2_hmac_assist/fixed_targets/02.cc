#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(struct t_hash_state) * 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct t_hash_state inner;
  struct t_hash_state outer;
  size_t consumed = stream.ConsumeData(&inner, sizeof(inner));
  if (consumed != sizeof(inner)) {
    return 0;
  }
  consumed = stream.ConsumeData(&outer, sizeof(outer));
  if (consumed != sizeof(outer)) {
    return 0;
  }

  if (stream.remaining_bytes() < 2) {
    return 0;
  }

  size_t first_hmac_size = stream.ConsumeIntegralInRange<size_t>(1, stream.remaining_bytes() / 2);
  std::string first_hmac = stream.ConsumeBytesAsString(first_hmac_size);

  size_t result_size = stream.remaining_bytes();
  std::string result = stream.ConsumeBytesAsString(result_size);

  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  SHA224_pbkdf2_hmac_assist(&inner, &outer, const_cast<char*>(first_hmac.c_str()), const_cast<char*>(result.c_str()), iterations, digest_size);

  return 0;
}