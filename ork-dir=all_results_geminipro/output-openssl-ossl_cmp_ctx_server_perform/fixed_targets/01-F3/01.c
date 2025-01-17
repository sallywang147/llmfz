#include <fuzzer/FuzzedDataProvider.h>

#include <openssl/cmp.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string client_pem = stream.ConsumeRemainingBytesAsString();
  BIO* client_bio = BIO_new_mem_buf(client_pem.data(), client_pem.size());
  X509* client_cert = PEM_read_bio_X509(client_bio, nullptr, nullptr, nullptr);
  BIO_free(client_bio);
  if (client_cert == nullptr) {
    return 0;
  }

  const std::string request_der = stream.ConsumeRemainingBytesAsString();
  uint8_t* request_ptr =
      static_cast<uint8_t*>(malloc(request_der.size()));
  memcpy(request_ptr, request_der.data(), request_der.size());
  OSSL_CMP_MSG* request =
      OSSL_CMP_MSG_create_from_der(request_ptr, request_der.size());
  free(request_ptr);
  if (request == nullptr) {
    X509_free(client_cert);
    return 0;
  }

  OSSL_CMP_CTX* client_ctx = OSSL_CMP_CTX_new_server();
  if (client_ctx == nullptr) {
    OSSL_CMP_MSG_free(request);
    X509_free(client_cert);
    return 0;
  }

  OSSL_CMP_CTX_set0_cert(client_ctx, client_cert);
  OSSL_CMP_MSG* response = OSSL_CMP_CTX_server_perform(client_ctx, request);

  OSSL_CMP_CTX_free(client_ctx);
  OSSL_CMP_MSG_free(request);
  OSSL_CMP_MSG_free(response);

  return 0;
}