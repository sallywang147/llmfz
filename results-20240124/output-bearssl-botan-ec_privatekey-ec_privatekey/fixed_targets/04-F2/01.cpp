#include <botan/botan.h>
#include <botan/ec_key.h>

extern "C" {
#include <botan/ffi.h>
}

void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Fix the build error by calling the function `void Botan::EC_PrivateKey::EC_PrivateKey(Botan::EC_PrivateKey * , char ** , Botan::AlgorithmIdentifier * , char * , size_t , bool )`
  Botan::EC_PrivateKey ec_key;
  ec_key.load_key(data, size);
}