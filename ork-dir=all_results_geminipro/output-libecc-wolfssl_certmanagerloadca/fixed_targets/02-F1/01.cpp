#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "wolfssl/options.h"
#include "wolfssl/ssl.h"

extern "C" {
#include "wolfssl/wolfcrypt/sha256.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  WOLFSSL_CERT_MANAGER* cert_manager = wolfSSL_CertManagerNew();
  if (cert_manager == nullptr) {
    return 0;
  }

  const std::string cert_file = stream.ConsumeRemainingBytesAsString();
  const std::string key_file = stream.ConsumeRemainingBytesAsString();

  wolfSSL_CertManagerLoadCA(cert_manager, const_cast<char*>(cert_file.c_str()),
                           const_cast<char*>(key_file.c_str()));
  wolfSSL_CertManagerFree(cert_manager);
  return 0;
}