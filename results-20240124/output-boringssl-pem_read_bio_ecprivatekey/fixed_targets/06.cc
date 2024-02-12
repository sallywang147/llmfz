 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <openssl/bio.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  BIO* bio = BIO_new_mem_buf(data, size);
  if (bio == nullptr) {
    return 0;
  }

  EC_KEY* key = nullptr;
  PEM_read_bio_ECPrivateKey(bio, &key, nullptr, nullptr);
  if (key != nullptr) {
    EC_KEY_free(key);
  }
  BIO_free(bio);

  return 0;
}