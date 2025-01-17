#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/ssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  wolfSSL_Init();

  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == nullptr) {
    return 0;
  }

  // Divide the data into two parts: one for the file and one for the path.
  size_t dataSize = provider.remaining_bytes();
  size_t firstSize = provider.ConsumeIntegralInRange<size_t>(1, dataSize - 1);
  std::string file = provider.ConsumeBytesAsString(firstSize);
  std::string path = provider.ConsumeRemainingBytesAsString();

  wolfSSL_CertManagerLoadCA(cm, file.c_str(), path.c_str());

  wolfSSL_CertManagerFree(cm);
  wolfSSL_Cleanup();

  return 0;
}