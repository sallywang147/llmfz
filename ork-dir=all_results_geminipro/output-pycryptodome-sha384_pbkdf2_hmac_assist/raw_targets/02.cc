#include <fuzzer/FuzzedDataProvider.h>

#include <string.h>

#include "sha384.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  std::vector<uint8_t> first_hmac = stream.ConsumeBytes<uint8_t>(digest_size);
  std::vector<uint8_t> result = stream.ConsumeBytes<uint8_t>(digest_size);

  struct t_hash_state inner, outer;
  SHA384_Init(&inner);
  SHA384_Init(&outer);

  int ret = SHA384_pbkdf2_hmac_assist(&inner, &outer, first_hmac.data(), result.data(),
                                     iterations, digest_size);
  if (ret != 0) {
    return 0;
  }

  return 0;
}