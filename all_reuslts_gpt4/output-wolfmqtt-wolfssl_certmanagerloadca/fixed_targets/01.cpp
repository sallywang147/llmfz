#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wolfssl/wolfcrypt/settings.h"
#include "wolfssl/ssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    wolfSSL_Init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == NULL) {
    return 0;
  }

  std::string file = provider.ConsumeRandomLengthString();
  std::string path = provider.ConsumeRemainingBytesAsString();

  wolfSSL_CertManagerLoadCA(cm, file.c_str(), path.c_str());

  wolfSSL_CertManagerFree(cm);

  return 0;
}