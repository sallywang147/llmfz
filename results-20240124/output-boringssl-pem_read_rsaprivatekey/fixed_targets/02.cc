 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string pem_key = stream.ConsumeRemainingBytesAsString();
  FILE* key_file = fmemopen((void*)pem_key.c_str(), pem_key.size(), "r");
  if (key_file == nullptr) {
    return 0;
  }

  RSA* rsa = PEM_read_RSAPrivateKey(key_file, nullptr, nullptr, nullptr);
  if (rsa == nullptr) {
    return 0;
  }

  RSA_free(rsa);
  fclose(key_file);
  return 0;
}