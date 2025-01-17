#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "md5.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct t_hash_state inner;
  struct t_hash_state outer;

  std::vector<char> first_hmac = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange<size_t>(0, size));
  std::vector<char> result = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange<size_t>(0, size));
  
  size_t iterations = stream.ConsumeIntegral<size_t>();

  MD5_pbkdf2_hmac_assist(&inner, &outer, first_hmac.data(), result.data(), iterations);

  return 0;
}