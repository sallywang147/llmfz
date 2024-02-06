#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/cms.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <openssl/err.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenSSL
  ERR_load_crypto_strings();
  OpenSSL_add_all_algorithms();

  // Create and initialize the required parameters for the function
  CMS_SignedData_st* sd = CMS_SignedData_new();
  BIO* detached_data = BIO_new(BIO_s_mem());
  STACK_OF(X509)* scerts = sk_X509_new_null();
  X509_STORE* store = X509_STORE_new();
  STACK_OF(X509)* extra = sk_X509_new_null();
  STACK_OF(X509_CRL)* crls = sk_X509_CRL_new_null();
  int flags = stream.ConsumeIntegral<int>();
  OSSL_LIB_CTX* libctx = OSSL_LIB_CTX_new();
  std::string propq = stream.ConsumeRandomLengthString();
  
  if (!sd || !detached_data || !scerts || !store || !extra || !crls || !libctx) {
    // If any of the above initializations failed, clean up and return
    CMS_SignedData_free(sd);
    BIO_free(detached_data);
    sk_X509_free(scerts);
    X509_STORE_free(store);
    sk_X509_free(extra);
    sk_X509_CRL_free(crls);
    OSSL_LIB_CTX_free(libctx);
    return 0;
  }

  // Call the function to be fuzzed
  BIO* result = CMS_SignedData_verify(sd, detached_data, scerts, store, extra, crls, flags, libctx, const_cast<char*>(propq.c_str()));

  // Clean up
  CMS_SignedData_free(sd);
  BIO_free(detached_data);
  sk_X509_free(scerts);
  X509_STORE_free(store);
  sk_X509_free(extra);
  sk_X509_CRL_free(crls);
  OSSL_LIB_CTX_free(libctx);
  BIO_free(result);

  return 0;
}