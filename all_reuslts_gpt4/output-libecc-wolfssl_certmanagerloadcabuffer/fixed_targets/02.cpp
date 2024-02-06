#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wolfssl/options.h"
#include "wolfssl/ssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    wolfSSL_Init();
    initialized = true;
  }

  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == nullptr) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Consume data for the buffer
  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string buffer = stream.ConsumeBytesAsString(buffer_size);

  // Consume data for the format
  int format = stream.ConsumeIntegral<int>();

  wolfSSL_CertManagerLoadCABuffer(cm, buffer.data(), buffer.size(), format);

  wolfSSL_CertManagerFree(cm);

  return 0;
}