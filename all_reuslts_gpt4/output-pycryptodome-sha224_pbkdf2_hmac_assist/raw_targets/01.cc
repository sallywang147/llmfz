#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "hash.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string first_hmac = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string result = stream.ConsumeRemainingBytesAsString();

  // Initialize struct pointers
  struct t_hash_state inner;
  struct t_hash_state outer;

  // Call the function to fuzz
  SHA224_pbkdf2_hmac_assist(&inner, &outer, const_cast<char*>(first_hmac.c_str()), const_cast<char*>(result.c_str()), iterations, digest_size);

  return 0;
}