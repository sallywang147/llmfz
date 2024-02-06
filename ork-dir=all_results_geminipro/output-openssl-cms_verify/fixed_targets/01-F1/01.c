#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/bio.h>
#include <openssl/cms.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a CMS_ContentInfo structure.
  CMS_ContentInfo* cms = CMS_ContentInfo_new();
  if (cms == NULL) {
    return 0;
  }

  // Create a BIO object to hold the CMS data.
  BIO* bio = BIO_new_mem_buf(data, size);
  if (bio == NULL) {
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Parse the CMS data.
  int ret = CMS_verify(cms, NULL, NULL, bio, NULL, 0);
  if (ret != 1) {
    BIO_free(bio);
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Create a stack of X509 certificates.
  STACK_OF(X509)* certs = sk_X509_new_null();
  if (certs == NULL) {
    BIO_free(bio);
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Create a BIO object to hold the certificate data.
  BIO* cert_bio = BIO_new_mem_buf(data, size);
  if (cert_bio == NULL) {
    sk_X509_free(certs);
    BIO_free(bio);
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Parse the certificate data.
  X509* cert = PEM_read_bio_X509(cert_bio, NULL, NULL, NULL);
  if (cert == NULL) {
    BIO_free(cert_bio);
    sk_X509_free(certs);
    BIO_free(bio);
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Add the certificate to the stack.
  sk_X509_push(certs, cert);

  // Create an X509 store.
  X509_STORE* store = X509_STORE_new();
  if (store == NULL) {
    X509_free(cert);
    sk_X509_free(certs);
    BIO_free(cert_bio);
    BIO_free(bio);
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Add the certificate to the store.
  X509_STORE_add_cert(store, cert);

  // Create a BIO object to hold the output data.
  BIO* out = BIO_new(BIO_s_mem());
  if (out == NULL) {
    X509_STORE_free(store);
    X509_free(cert);
    sk_X509_free(certs);
    BIO_free(cert_bio);
    BIO_free(bio);
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Verify the CMS data.
  ret = CMS_verify(cms, certs, store, bio, out, 0);
  if (ret != 1) {
    BIO_free(out);
    X509_STORE_free(store);
    X509_free(cert);
    sk_X509_free(certs);
    BIO_free(cert_bio);
    BIO_free(bio);
    CMS_ContentInfo_free(cms);
    return 0;
  }

  // Free the resources.
  BIO_free(out);
  X509_STORE_free(store);
  X509_free(cert);
  sk_X509_free(certs);
  BIO_free(cert_bio);
  BIO_free(bio);
  CMS_ContentInfo_free(cms);

  return 0;
}