#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

extern "C" {
#include <openssl/pem.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  BIO* bio = BIO_new_mem_buf(data, size);
  if (bio == nullptr) {
    return 0;
  }
  struct evp_pkey_st* pkey = nullptr;
  PEM_read_bio_PrivateKey(bio, &pkey, nullptr, nullptr);
  BIO_free(bio);
  if (pkey != nullptr) {
    EVP_PKEY_free(pkey);
  }
  return 0;
}