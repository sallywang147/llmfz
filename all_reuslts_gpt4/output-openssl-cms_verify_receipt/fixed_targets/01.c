#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/cms.h>
#include <openssl/err.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenSSL
  OpenSSL_add_all_algorithms();
  ERR_load_crypto_strings();

  // Create CMS_ContentInfo_st objects
  CMS_ContentInfo *rcms = CMS_ContentInfo_new();
  CMS_ContentInfo *ocms = CMS_ContentInfo_new();

  // Create stack_st_X509 object
  STACK_OF(X509) *certs = sk_X509_new_null();

  // Create x509_store_st object
  X509_STORE *store = X509_STORE_new();

  // Consume data from the stream to generate flags
  int flags = stream.ConsumeIntegral<int>();

  // Call the target function
  int result = CMS_verify_receipt(rcms, ocms, certs, store, flags);

  // Cleanup
  CMS_ContentInfo_free(rcms);
  CMS_ContentInfo_free(ocms);
  sk_X509_pop_free(certs, X509_free);
  X509_STORE_free(store);

  return 0;
}