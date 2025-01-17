#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/cms.h>
#include <openssl/err.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenSSL
  OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS | OPENSSL_INIT_ADD_ALL_CIPHERS
    | OPENSSL_INIT_ADD_ALL_DIGESTS, nullptr);

  // Create a BIO object from the data
  BIO *bio = BIO_new_mem_buf(stream.ConsumeRemainingBytes().data(), size);

  // Create a CMS_ContentInfo object
  CMS_ContentInfo *cms = d2i_CMS_bio(bio, nullptr);
  if (cms == nullptr) {
    BIO_free(bio);
    return 0;
  }

  // Create a X509_STORE object
  X509_STORE *store = X509_STORE_new();
  if (store == nullptr) {
    CMS_ContentInfo_free(cms);
    BIO_free(bio);
    return 0;
  }

  // Create an empty stack of X509 certificates
  STACK_OF(X509) *certs = sk_X509_new_null();
  if (certs == nullptr) {
    X509_STORE_free(store);
    CMS_ContentInfo_free(cms);
    BIO_free(bio);
    return 0;
  }

  // Create a BIO object for output
  BIO *out = BIO_new(BIO_s_mem());
  if (out == nullptr) {
    sk_X509_free(certs);
    X509_STORE_free(store);
    CMS_ContentInfo_free(cms);
    BIO_free(bio);
    return 0;
  }

  // Call the function to be fuzzed
  int flags = stream.ConsumeIntegral<int>();
  CMS_verify(cms, certs, store, nullptr, out, flags);

  // Cleanup
  BIO_free(out);
  sk_X509_free(certs);
  X509_STORE_free(store);
  CMS_ContentInfo_free(cms);
  BIO_free(bio);

  return 0;
}