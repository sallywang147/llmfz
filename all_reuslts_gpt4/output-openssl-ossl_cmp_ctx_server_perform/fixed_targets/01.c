#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/cmp.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize OpenSSL
  OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS | OPENSSL_INIT_LOAD_SSL_STRINGS, NULL);

  // Create a CMP context
  OSSL_CMP_CTX *ctx = OSSL_CMP_CTX_new(NULL, NULL);
  if (ctx == NULL) {
    return 0;
  }

  // Create a CMP message
  OSSL_CMP_MSG *msg = OSSL_CMP_MSG_new();
  if (msg == NULL) {
    OSSL_CMP_CTX_free(ctx);
    return 0;
  }

  // Consume data from the fuzzer input
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
  if (bytes.empty()) {
    OSSL_CMP_MSG_free(msg);
    OSSL_CMP_CTX_free(ctx);
    return 0;
  }

  // Load the data into the CMP message
  if (OSSL_CMP_MSG_load(msg, bytes.data(), bytes.size()) != 1) {
    OSSL_CMP_MSG_free(msg);
    OSSL_CMP_CTX_free(ctx);
    return 0;
  }

  // Perform the server operation
  OSSL_CMP_CTX_server_perform(ctx, msg);

  // Cleanup
  OSSL_CMP_MSG_free(msg);
  OSSL_CMP_CTX_free(ctx);

  return 0;
}