#include <fuzzer/FuzzedDataProvider.h>
#include <wolfssl/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == nullptr) {
    return 0;
  }

  std::string buffer = stream.ConsumeRandomLengthString();
  int format = stream.ConsumeIntegral<int>();
  int type = stream.ConsumeIntegral<int>();
  int verify = stream.ConsumeIntegral<int>();

  wolfSSL_CertManagerLoadCABuffer_ex(cm, buffer.c_str(), buffer.size(), format, type, verify);

  wolfSSL_CertManagerFree(cm);

  return 0;
}