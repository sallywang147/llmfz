#include <botan/botan.h>
#include <botan/ec_key.h>

extern "C" {
#include <botan/botan.h>
#include <botan/ec_key.h>
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Botan::EC_PrivateKey key;
  // ...
}