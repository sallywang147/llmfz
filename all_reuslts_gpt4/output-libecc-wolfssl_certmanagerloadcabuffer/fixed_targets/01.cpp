#include <fuzzer/FuzzedDataProvider.h>
#include <wolfssl/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == nullptr) {
    return 0;
  }

  const size_t buffer_size = stream.remaining_bytes() / 2;
  std::string buffer = stream.ConsumeBytesAsString(buffer_size);
  int format = stream.ConsumeIntegral<int>();

  wolfSSL_CertManagerLoadCABuffer(cm, buffer.c_str(), buffer.size(), format);

  wolfSSL_CertManagerFree(cm);

  return 0;
}