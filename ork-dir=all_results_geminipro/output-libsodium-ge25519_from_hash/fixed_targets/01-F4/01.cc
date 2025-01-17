#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include <ge25519.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char s[32];
  char h[32];

  stream.ConsumeBytes(s, sizeof(s));
  stream.ConsumeBytes(h, sizeof(h));

  ge25519_from_hash(s, h);

  return 0;
}