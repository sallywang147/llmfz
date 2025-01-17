#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <openssl/ec.h>
#include <openssl/pem.h>

extern "C" {
#include <openssl/bio.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string pem_data = stream.ConsumeRemainingBytesAsString();
  struct ec_key_st *key = nullptr;
  BIO *bio = BIO_new_mem_buf(const_cast<char*>(pem_data.c_str()), -1);
  if (bio == nullptr) {
    return 0;
  }
  PEM_read_bio_ECPrivateKey(bio, &key, nullptr, nullptr);
  BIO_free(bio);
  EC_KEY_free(key);
  return 0;
}