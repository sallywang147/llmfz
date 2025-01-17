#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include <openssl/bio.h>
#include <openssl/cms.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/stack.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  BIO* detached_data = BIO_new(BIO_s_mem());
  if (detached_data == nullptr) {
    return 0;
  }
  BIO_write(detached_data, stream.ConsumeRemainingBytes().data(),
            stream.ConsumeRemainingBytes().size());

  CMS_SignedData* sd = d2i_CMS_SignedData(nullptr, &data, size);
  if (sd == nullptr) {
    BIO_free(detached_data);
    return 0;
  }

  STACK_OF(X509)* scerts = sk_X509_new_null();
  if (scerts == nullptr) {
    BIO_free(detached_data);
    CMS_SignedData_free(sd);
    return 0;
  }

  X509_STORE* store = X509_STORE_new();
  if (store == nullptr) {
    BIO_free(detached_data);
    CMS_SignedData_free(sd);
    sk_X509_free(scerts);
    return 0;
  }

  STACK_OF(X509)* extra = sk_X509_new_null();
  if (extra == nullptr) {
    BIO_free(detached_data);
    CMS_SignedData_free(sd);
    sk_X509_free(scerts);
    X509_STORE_free(store);
    return 0;
  }

  STACK_OF(X509_CRL)* crls = sk_X509_CRL_new_null();
  if (crls == nullptr) {
    BIO_free(detached_data);
    CMS_SignedData_free(sd);
    sk_X509_free(scerts);
    X509_STORE_free(store);
    sk_X509_free(extra);
    return 0;
  }

  int result = CMS_SignedData_verify(sd, detached_data, scerts, store, extra,
                                     crls, 0, nullptr, nullptr);

  BIO_free(detached_data);
  CMS_SignedData_free(sd);
  sk_X509_free(scerts);
  X509_STORE_free(store);
  sk_X509_free(extra);
  sk_X509_CRL_free(crls);

  return result;
}