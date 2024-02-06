#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenSSL
  SSL_library_init();
  SSL_load_error_strings();

  // Create new SSL context
  SSL_CTX *ctx = SSL_CTX_new(TLS_client_method());
  if (ctx == nullptr) {
    return 0;
  }

  // Create new SSL structure
  SSL *ssl = SSL_new(ctx);
  if (ssl == nullptr) {
    SSL_CTX_free(ctx);
    return 0;
  }

  // Call the target function
  bool result = nts_ke_request(ssl);

  // Free the SSL structure and context
  SSL_free(ssl);
  SSL_CTX_free(ctx);

  return 0;
}