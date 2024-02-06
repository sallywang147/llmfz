#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  SSL_CTX *ctx = SSL_CTX_new(DTLS_method());
  if (ctx == nullptr) {
    return 0;
  }

  SSL *ssl = SSL_new(ctx);
  if (ssl == nullptr) {
    SSL_CTX_free(ctx);
    return 0;
  }

  int cmd = stream.ConsumeIntegral<int>();
  size_t larg = stream.ConsumeIntegral<size_t>();
  std::string parg = stream.ConsumeRemainingBytesAsString();

  dtls1_ctrl(ssl, cmd, larg, const_cast<char *>(parg.c_str()));

  SSL_free(ssl);
  SSL_CTX_free(ctx);

  return 0;
}