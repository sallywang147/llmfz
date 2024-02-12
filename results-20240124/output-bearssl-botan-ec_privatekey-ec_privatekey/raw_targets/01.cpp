 #include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "botan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Botan::EC_PrivateKey* ec_private_key = new Botan::EC_PrivateKey;
  char** arg1 = new char*[stream.ConsumeIntegralInRange<size_t>(0, 10)];
  for (size_t i = 0; i < stream.ConsumeIntegralInRange<size_t>(0, 10); i++) {
    arg1[i] = new char[stream.ConsumeIntegralInRange<size_t>(0, 10)];
  }
  Botan::AlgorithmIdentifier* arg2 = new Botan::AlgorithmIdentifier;
  char* arg3 = new char[stream.ConsumeIntegralInRange<size_t>(0, 10)];
  size_t arg4 = stream.ConsumeIntegralInRange<size_t>(0, 10);
  bool arg5 = stream.ConsumeBool();

  ec_private_key->EC_PrivateKey(arg1, arg2, arg3, arg4, arg5);

  for (size_t i = 0; i < stream.ConsumeIntegralInRange<size_t>(0, 10); i++) {
    delete[] arg1[i];
  }
  delete[] arg1;
  delete arg2;
  delete[] arg3;
  delete ec_private_key;
  return 0;
}