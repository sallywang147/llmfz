 #include <fuzzer/FuzzedDataProvider.h>

#include <openssl/bio.h>
#include <openssl/ec.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BIO* bio = BIO_new_mem_buf((void*)data, size);
  if (bio == nullptr) {
    return 0;
  }

  EC_KEY* key = nullptr;
  PEM_read_bio_ECPrivateKey(bio, &key, nullptr, nullptr);

  BIO_free(bio);
  EC_KEY_free(key);

  return 0;
}