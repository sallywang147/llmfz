 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  Botan::EC_PrivateKey a;
  char* b = nullptr;
  Botan::AlgorithmIdentifier c;
  char* d = nullptr;
  bool e = false;
  a.EC_PrivateKey(&a, &b, &c, d, size, e);
  return 0;
}