#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "openssl/bio.h"
#include "openssl/evp.h"
#include "openssl/pem.h"
#include "openssl/rsa.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BIO* bio = BIO_new_mem_buf(data, size);
  if (bio == nullptr) {
    return 0;
  }

  RSA* rsa = nullptr;
  PEM_read_bio_RSAPrivateKey(bio, &rsa, nullptr, nullptr);
  BIO_free(bio);

  // Call the function that was not called by the fuzz target
  PEM_read_RSAPrivateKey(bio, &rsa, nullptr, nullptr);

  return 0;
}