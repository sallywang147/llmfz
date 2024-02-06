#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char s[32];
  char h[32];

  stream.ConsumeBytes(s, 32);
  stream.ConsumeBytes(h, 32);

  ge25519_from_hash(s, h);

  return 0;
}