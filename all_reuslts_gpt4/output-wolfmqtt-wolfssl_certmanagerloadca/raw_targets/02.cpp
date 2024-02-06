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

  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  const std::string file = provider.ConsumeRandomLengthString();
  const std::string path = provider.ConsumeRemainingBytesAsString();

  wolfSSL_CertManagerLoadCA(cm, const_cast<char*>(file.c_str()), const_cast<char*>(path.c_str()));

  wolfSSL_CertManagerFree(cm);

  return 0;
}