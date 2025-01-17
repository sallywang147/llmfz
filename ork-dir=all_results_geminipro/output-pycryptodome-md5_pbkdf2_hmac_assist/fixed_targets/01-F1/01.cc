#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fuzzer/FuzzedDataProvider.h>

#define MD5_PBKDF2_HMAC_ASSIST_SIZE 16

extern "C" {
#include <md5.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < MD5_PBKDF2_HMAC_ASSIST_SIZE * 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  uint8_t inner_key[MD5_PBKDF2_HMAC_ASSIST_SIZE];
  uint8_t outer_key[MD5_PBKDF2_HMAC_ASSIST_SIZE];
  uint8_t first_hmac[MD5_PBKDF2_HMAC_ASSIST_SIZE];
  uint8_t result[MD5_PBKDF2_HMAC_ASSIST_SIZE];
  size_t iterations = 0;

  stream.ConsumeBytes<uint8_t>(inner_key, MD5_PBKDF2_HMAC_ASSIST_SIZE);
  stream.ConsumeBytes<uint8_t>(outer_key, MD5_PBKDF2_HMAC_ASSIST_SIZE);
  stream.ConsumeBytes<uint8_t>(first_hmac, MD5_PBKDF2_HMAC_ASSIST_SIZE);
  iterations = stream.ConsumeIntegral<size_t>();

  MD5_pbkdf2_hmac_assist(
      (struct t_hash_state *)inner_key,
      (struct t_hash_state *)outer_key,
      (char *)first_hmac,
      (char *)result,
      iterations);

  return 0;
}