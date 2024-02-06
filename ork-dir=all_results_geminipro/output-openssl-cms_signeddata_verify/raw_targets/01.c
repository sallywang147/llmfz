#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <openssl/bio.h>
#include <openssl/cms.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a CMS_SignedData structure to hold the signature.
  CMS_SignedData* sd = CMS_SignedData_create();
  if (sd == nullptr) {
    ERR_print_errors_fp(stderr);
    return 0;
  }

  // Create a BIO to hold the detached data.
  BIO* detached_data = BIO_new_mem_buf(data, size);
  if (detached_data == nullptr) {
    ERR_print_errors_fp(stderr);
    CMS_SignedData_free(sd);
    return 0;
  }

  // Create a stack of X509 certificates to hold the signer's certificate.
  STACK_OF(X509)* scerts = sk_X509_new_null();
  if (scerts == nullptr) {
    ERR_print_errors_fp(stderr);
    CMS_SignedData_free(sd);
    BIO_free(detached_data);
    return 0;
  }

  // Create an X509 store to hold the signer's certificate.
  X509_STORE* store = X509_STORE_new();
  if (store == nullptr) {
    ERR_print_errors_fp(stderr);
    CMS_SignedData_free(sd);
    BIO_free(detached_data);
    sk_X509_free(scerts);
    return 0;
  }

  // Create a stack of X509 certificates to hold any extra certificates.
  STACK_OF(X509)* extra = sk_X509_new_null();
  if (extra == nullptr) {
    ERR_print_errors_fp(stderr);
    CMS_SignedData_free(sd);
    BIO_free(detached_data);
    sk_X509_free(scerts);
    X509_STORE_free(store);
    return 0;
  }

  // Create a stack of X509 CRLs to hold any CRLs.
  STACK_OF(X509_CRL)* crls = sk_X509_CRL_new_null();
  if (crls == nullptr) {
    ERR_print_errors_fp(stderr);
    CMS_SignedData_free(sd);
    BIO_free(detached_data);
    sk_X509_free(scerts);
    X509_STORE_free(store);
    sk_X509_free(extra);
    return 0;
  }

  // Set the flags for the verification.
  int flags = 0;

  // Create an OpenSSL library context.
  OSSL_LIB_CTX* libctx = OSSL_LIB_CTX_new();
  if (libctx == nullptr) {
    ERR_print_errors_fp(stderr);
    CMS_SignedData_free(sd);
    BIO_free(detached_data);
    sk_X509_free(scerts);
    X509_STORE_free(store);
    sk_X509_free(extra);
    sk_X509_CRL_free(crls);
    return 0;
  }

  // Create a property query string.
  char* propq = nullptr;

  // Verify the signature.
  struct bio_st* result = CMS_SignedData_verify(sd, detached_data, scerts, store,
                                                extra, crls, flags, libctx, propq);

  // Free the resources.
  CMS_SignedData_free(sd);
  BIO_free(detached_data);
  sk_X509_free(scerts);
  X509_STORE_free(store);
  sk_X509_free(extra);
  sk_X509_CRL_free(crls);
  OSSL_LIB_CTX_free(libctx);

  return 0;
}