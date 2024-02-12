#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include <openssl/dsa.h>
#include <openssl/pem.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  BIO* bio = BIO_new(BIO_s_mem());
  if (bio == nullptr) {
    return 0;
  }
  BIO_write(bio, data, size);

  DSA* dsa = nullptr;
  PEM_read_DSAPrivateKey(bio, &dsa, nullptr, nullptr);
  DSA_free(dsa);

  BIO_free(bio);
  return 0;
}