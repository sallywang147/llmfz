#include "common.h"
#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/sha.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (!size)
    return 0;

  FuzzedDataProvider stream(data, size);
  SHA256_CTX inner;
  SHA256_CTX outer;
  SHA256_Init(&inner);
  SHA256_Init(&outer);

  size_t num_bytes = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> password = stream.ConsumeBytes<uint8_t>(num_bytes);

  num_bytes = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> salt = stream.ConsumeBytes<uint8_t>(num_bytes);

  size_t iterations = stream.ConsumeIntegral<size_t>();
  size_t digest_size = stream.ConsumeIntegral<size_t>();

  std::vector<uint8_t> result(digest_size);
  SHA224_pbkdf2_hmac_assist(&inner, &outer, reinterpret_cast<char*>(password.data()),
                            reinterpret_cast<char*>(salt.data()), iterations, digest_size);
  SHA256_Final(reinterpret_cast<unsigned char*>(result.data()), &outer);

  return 0;
}