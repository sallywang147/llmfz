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

  FuzzedDataProvider stream(data, size);

  wolfSSL_Init();

  WOLFSSL_CERT_MANAGER* cm = wolfSSL_CertManagerNew();
  if (cm == NULL) {
    wolfSSL_Cleanup();
    return 0;
  }

  std::string ca_file = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string verify_file = stream.ConsumeRemainingBytesAsString();

  wolfSSL_CertManagerLoadCA(cm, ca_file.c_str(), verify_file.c_str());

  wolfSSL_CertManagerFree(cm);
  wolfSSL_Cleanup();

  return 0;
}