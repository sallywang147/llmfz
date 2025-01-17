#include <fuzzer/FuzzedDataProvider.h>
#include <string.h>

extern "C" {
#include "sha384.h"
}

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

  int ret = SHA384_pbkdf2_hmac_assist_inner(&inner, &outer, first_hmac.data(), result.data(),
                                     iterations, digest_size);
  if (ret != 0) {
    return 0;
  }

  return 0;
}

int SHA384_pbkdf2_hmac_assist_inner(struct t_hash_state *pInner, struct t_hash_state *pOuter,
                                  const uint8_t *first_hmac, const uint8_t *result,
                                  size_t iterations, size_t digest_size) {
  uint8_t tmp[SHA384_DIGEST_SIZE];
  uint8_t U[SHA384_DIGEST_SIZE];
  uint8_t T[SHA384_DIGEST_SIZE];
  uint32_t i;

  SHA384_Update(pInner, first_hmac, digest_size);
  SHA384_Final(U, pInner);

  for (i = 1; i <= iterations; i++) {
    SHA384_Init(pInner);
    SHA384_Update(pInner, U, digest_size);
    SHA384_Final(tmp, pInner);

    SHA384_Init(pOuter);
    SHA384_Update(pOuter, result, digest_size);
    SHA384_Update(pOuter, tmp, digest_size);
    SHA384_Final(T, pOuter);

    memcpy(U, T, digest_size);
  }

  memcpy(result, U, digest_size);

  return 0;
}