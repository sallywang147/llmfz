#include <fuzzer/FuzzedDataProvider.h>
#include <wolfssl/options.h>
#include <wolfssl/ssl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new WOLFSSL_CERT_MANAGER
  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == nullptr) {
    return 0;
  }

  // Extract a string from the data provider
  size_t str_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::string str = stream.ConsumeBytesAsString(str_size);
  char* buffer = const_cast<char*>(str.c_str());

  // Extract format, type and verify arguments from the data provider
  int format = stream.ConsumeIntegral<int>();
  int type = stream.ConsumeIntegral<int>();
  int verify = stream.ConsumeIntegral<int>();

  // Call the target function
  wolfSSL_CertManagerLoadCABuffer_ex(cm, buffer, str_size, format, type, verify);

  // Clean up
  wolfSSL_CertManagerFree(cm);

  return 0;
}