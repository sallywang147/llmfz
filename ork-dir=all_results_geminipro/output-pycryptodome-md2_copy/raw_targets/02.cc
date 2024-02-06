#include "common.h"
#include <fuzzer/FuzzedDataProvider.h>

#ifndef HASHTYPE
#error Macro HASHTYPE must be defined.
#endif

#ifndef FNAME
#error Macro FNAME must be defined.
#endif

#define CONCAT_TYPE(x) _PASTE2(HASHTYPE, x)

#define init CONCAT_TYPE(_init)
#define update CONCAT_TYPE(_update)
#define digest CONCAT_TYPE(_digest)
#define destroy CONCAT_TYPE(_destroy)
#define copy CONCAT_TYPE(_copy)

#define STR(x) #x
#define INCLUDE(x) STR(x)

#include INCLUDE(FNAME)

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (!size)
    return 0;

  FuzzedDataProvider stream(data, size);
  hash_state *hs1;
  hash_state *hs2;
  if (init(&hs1) || init(&hs2))
    return 0;

  while (stream.remaining_bytes()) {
    size_t num_bytes = stream.ConsumeIntegral<size_t>();
    std::vector<uint8_t> buffer = stream.ConsumeBytes<uint8_t>(num_bytes);

    if (update(hs1, buffer.data(), buffer.size()))
      goto error;
  }

  copy(hs1, hs2);

  uint8_t result1[DIGEST_SIZE];
  uint8_t result2[DIGEST_SIZE];

#ifndef DIGEST_THIRD_PARAM
  digest(hs1, result1);
  digest(hs2, result2);
#else
  digest(hs1, result1, DIGEST_SIZE);
  digest(hs2, result2, DIGEST_SIZE);
#endif

  for (int i = 0; i < DIGEST_SIZE; ++i) {
    if (result1[i] != result2[i])
      goto error;
  }

error:
  destroy(hs1);
  destroy(hs2);
  return 0;
}