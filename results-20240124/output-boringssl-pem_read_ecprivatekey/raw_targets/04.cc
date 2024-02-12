 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <openssl/ec.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  BIO *bio = BIO_new(BIO_s_mem());
  if (bio == nullptr) {
    return 0;
  }
  BIO_write(bio, data, size);

  EC_KEY *ec_key = nullptr;
  ec_key = PEM_read_ECPrivateKey(bio, nullptr, nullptr, nullptr);
  if (ec_key == nullptr) {
    BIO_free(bio);
    return 0;
  }

  EC_KEY_free(ec_key);
  BIO_free(bio);

  return 0;
}