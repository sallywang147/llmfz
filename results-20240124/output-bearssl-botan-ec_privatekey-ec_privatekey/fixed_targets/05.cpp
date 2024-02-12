#include <botan/botan.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  Botan::EC_PrivateKey ec_private_key;
  Botan::AlgorithmIdentifier algorithm_identifier;
  Botan::EC_PrivateKey::EC_PrivateKey(&ec_private_key, nullptr, &algorithm_identifier, nullptr, 0, false);
  return 0;
}