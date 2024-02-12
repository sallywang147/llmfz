#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <openssl/evp.h>

extern "C" {
#include <openssl/pem.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  FILE* file = fopen("/dev/null", "r");
  if (file == nullptr) {
    return 0;
  }

  EVP_PKEY* key = nullptr;
  PEM_read_PrivateKey(file, &key, nullptr, nullptr);
  EVP_PKEY_free(key);
  fclose(file);

  return 0;
}