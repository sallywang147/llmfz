#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <sodium.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char s[32];
  char h[32];

  stream.ConsumeBytes(s, 32);
  stream.ConsumeBytes(h, 32);

  crypto_generichash_state state;
  crypto_generichash_init(&state, NULL, 0, 32);
  crypto_generichash_update(&state, s, 32);
  crypto_generichash_update(&state, h, 32);
  crypto_generichash_final(&state, s, 32);

  // Call the missing function
  ge25519_from_hash(s, h);

  return 0;
}