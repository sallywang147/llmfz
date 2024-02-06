#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <wolfssl/options.h>
extern "C" {
#include <wolfssl/ssl.h>
}
#include <wolfssl/wolfcrypt/asn.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/x509.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  WOLFSSL_CERT_MANAGER* cert_manager = wolfSSL_CertManagerNew();
  if (cert_manager == nullptr) {
    return 0;
  }
  const std::string ca_path = stream.ConsumeRemainingBytesAsString();
  const std::string ca_file = stream.ConsumeRemainingBytesAsString();
  wolfSSL_CertManagerLoadCA(cert_manager, ca_path.c_str(), ca_file.c_str());
  wolfSSL_CertManagerFree(cert_manager);
  return 0;
}