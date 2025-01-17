#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/cms.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenSSL
  OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, nullptr);

  // Prepare the input parameters for CMS_SignedData_verify
  CMS_ContentInfo *cms = nullptr;
  BIO *in = BIO_new_mem_buf(data, size);
  if (in == nullptr) {
    return 0;
  }

  // Read the CMS_ContentInfo from the input data
  cms = d2i_CMS_bio(in, nullptr);
  if (cms == nullptr) {
    BIO_free(in);
    return 0;
  }

  // Prepare the output parameters for CMS_SignedData_verify
  BIO *out = BIO_new(BIO_s_mem());
  if (out == nullptr) {
    CMS_ContentInfo_free(cms);
    BIO_free(in);
    return 0;
  }

  // Prepare the remaining parameters for CMS_SignedData_verify
  X509_STORE *store = X509_STORE_new();
  STACK_OF(X509) *certs = nullptr;

  // Call the target function
  BIO *res = CMS_verify(cms, certs, store, in, out, CMS_NOINTERN);

  // Clean up
  BIO_free(in);
  BIO_free(out);
  CMS_ContentInfo_free(cms);
  X509_STORE_free(store);

  return 0;
}