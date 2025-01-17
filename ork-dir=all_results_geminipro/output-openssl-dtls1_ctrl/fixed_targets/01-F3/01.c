#include <fuzzer/FuzzedDataProvider.h>

#include <openssl/ssl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <openssl/dtls1.h>
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  SSL *ssl = SSL_new(TLS_method());
  if (ssl == nullptr) {
    return 0;
  }

  int cmd = stream.ConsumeIntegral<int>();
  size_t larg = stream.ConsumeIntegral<size_t>();

  std::vector<uint8_t> parg_data = stream.ConsumeBytes<uint8_t>(larg);

  size_t ret = dtls1_ctrl(ssl, cmd, larg, reinterpret_cast<char *>(parg_data.data()));

  SSL_free(ssl);
  return ret;
}