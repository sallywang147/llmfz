 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  Botan::EC_PrivateKey* ec_private_key = new Botan::EC_PrivateKey();
  char** arg1 = new char*[size];
  for (size_t i = 0; i < size; i++) {
    arg1[i] = new char[data[i]];
  }
  Botan::AlgorithmIdentifier* arg2 = new Botan::AlgorithmIdentifier();
  char* arg3 = new char[size];
  bool arg4 = data[size - 1] % 2 == 0;
  ec_private_key->EC_PrivateKey(ec_private_key, arg1, arg2, arg3, size, arg4);
  return 0;
}