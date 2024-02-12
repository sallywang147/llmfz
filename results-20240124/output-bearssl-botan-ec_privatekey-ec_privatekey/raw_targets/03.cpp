 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <botan/botan.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  Botan::EC_PrivateKey* private_key = new Botan::EC_PrivateKey();
  char** pass_phrase = new char*[1];
  Botan::AlgorithmIdentifier* alg_id = new Botan::AlgorithmIdentifier();
  char* salt = new char[1];
  size_t salt_len = 0;
  bool use_locking = false;
  void Botan::EC_PrivateKey::EC_PrivateKey(private_key, pass_phrase, alg_id, salt, salt_len, use_locking);
  delete private_key;
  delete[] pass_phrase;
  delete alg_id;
  delete[] salt;
  return 0;
}