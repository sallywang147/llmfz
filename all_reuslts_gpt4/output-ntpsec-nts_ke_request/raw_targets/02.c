#include "fuzzer/FuzzedDataProvider.h"
#include "nts_ke.h"
#include "ssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SSL library
  SSL_library_init();
  SSL_load_error_strings();
  const SSL_METHOD *method = SSLv23_client_method();
  SSL_CTX *ctx = SSL_CTX_new(method);
  if (ctx == nullptr) {
    return 0;
  }

  // Create new SSL structure
  SSL *ssl = SSL_new(ctx);
  if (ssl == nullptr) {
    SSL_CTX_free(ctx);
    return 0;
  }

  // Set SSL options
  SSL_set_options(ssl, SSL_OP_NO_SSLv2);

  // Call the target function
  bool result = nts_ke_request(ssl);

  // Clean up
  SSL_free(ssl);
  SSL_CTX_free(ctx);

  return 0;
}