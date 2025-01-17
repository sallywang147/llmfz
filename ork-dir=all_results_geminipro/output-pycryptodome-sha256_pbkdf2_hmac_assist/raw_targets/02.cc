#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

extern "C" int SHA256_pbkdf2_hmac_assist(struct t_hash_state *inner,
                                         struct t_hash_state *outer,
                                         char *first_hmac, char *result,
                                         size_t iterations, size_t digest_size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 64) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();
  if (digest_size > 1024) {
    return 0;
  }
  std::vector<uint8_t> first_hmac(digest_size);
  stream.ConsumeBytes<uint8_t>(first_hmac.data(), digest_size);
  std::vector<uint8_t> result(digest_size);
  SHA256_pbkdf2_hmac_assist(nullptr, nullptr, first_hmac.data(), result.data(),
                            iterations, digest_size);
  return 0;
}