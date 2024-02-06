#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "openssl/cms.h"
#include "openssl/pem.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenSSL
  OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, nullptr);

  // Create a BIO from the data
  BIO *bio = BIO_new_mem_buf(stream.ConsumeRemainingBytes().data(), size);
  if (bio == nullptr)
    return 0;

  // Read the CMS ContentInfo structures
  CMS_ContentInfo *rcms = d2i_CMS_bio(bio, nullptr);
  CMS_ContentInfo *ocms = d2i_CMS_bio(bio, nullptr);

  // Create an X509_STORE for the certificates
  X509_STORE *store = X509_STORE_new();
  if (store == nullptr) {
    CMS_ContentInfo_free(rcms);
    CMS_ContentInfo_free(ocms);
    BIO_free(bio);
    return 0;
  }

  // Create a STACK_OF(X509) for the certificates
  STACK_OF(X509) *certs = sk_X509_new_null();
  if (certs == nullptr) {
    X509_STORE_free(store);
    CMS_ContentInfo_free(rcms);
    CMS_ContentInfo_free(ocms);
    BIO_free(bio);
    return 0;
  }

  // Get flags
  int flags = stream.ConsumeIntegral<int>();

  // Call the target function
  CMS_verify_receipt(rcms, ocms, certs, store, flags);

  // Cleanup
  sk_X509_free(certs);
  X509_STORE_free(store);
  CMS_ContentInfo_free(rcms);
  CMS_ContentInfo_free(ocms);
  BIO_free(bio);

  return 0;
}