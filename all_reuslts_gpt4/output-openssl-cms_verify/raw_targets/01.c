#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/cms.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a memory buffer BIO
  BIO *in = BIO_new(BIO_s_mem());
  BIO_write(in, stream.data(), stream.size());

  // Create a CMS_ContentInfo structure
  CMS_ContentInfo *cms = d2i_CMS_bio(in, NULL);
  if (cms == NULL) {
    BIO_free(in);
    return 0;
  }

  // Create a X509_STORE for our certs
  X509_STORE *store = X509_STORE_new();
  if (store == NULL) {
    CMS_ContentInfo_free(cms);
    BIO_free(in);
    return 0;
  }

  // Create a stack of X509 certificates
  STACK_OF(X509) *certs = sk_X509_new_null();
  if (certs == NULL) {
    X509_STORE_free(store);
    CMS_ContentInfo_free(cms);
    BIO_free(in);
    return 0;
  }

  // Create a BIO for the output
  BIO *out = BIO_new(BIO_s_mem());

  // Create a BIO for the detached content
  BIO *dcont = NULL;

  // Generate a random flag
  int flags = stream.ConsumeIntegral<int>();

  // Call the function to be fuzzed
  CMS_verify(cms, certs, store, dcont, out, flags);

  // Cleanup
  BIO_free(out);
  sk_X509_pop_free(certs, X509_free);
  X509_STORE_free(store);
  CMS_ContentInfo_free(cms);
  BIO_free(in);

  return 0;
}