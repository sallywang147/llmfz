#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  Botan::EC_PrivateKey* ec_private_key = new Botan::EC_PrivateKey;
  char* argv[] = {""};
  Botan::AlgorithmIdentifier* algorithm_identifier = new Botan::AlgorithmIdentifier;
  uint8_t* key_data = new uint8_t[size];
  bool use_default_rng = false;

  ec_private_key->EC_PrivateKey(ec_private_key, argv, algorithm_identifier, key_data, size, use_default_rng);

  delete ec_private_key;
  delete[] argv;
  delete algorithm_identifier;
  delete[] key_data;

  return 0;
}