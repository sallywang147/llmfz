#include <fuzzer/FuzzedDataProvider.h>

#include <openssl/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  SSL_CTX* ctx = SSL_CTX_new(TLS_method());
  SSL* ssl = SSL_new(ctx);

  int cmd = stream.ConsumeIntegral<int>();
  size_t larg = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> parg = stream.ConsumeBytes<uint8_t>(larg);

  dtls1_ctrl(ssl, cmd, larg, reinterpret_cast<char*>(parg.data()));

  SSL_free(ssl);
  SSL_CTX_free(ctx);
  return 0;
}