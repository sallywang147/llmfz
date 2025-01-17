#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <wolfssl/wolfcrypt/asn.h>
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/logging.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/ssl.h>
#include <wolfssl/wolfcrypt/wc_port.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string file = stream.ConsumeRemainingBytesAsString();
  const std::string path = stream.ConsumeRemainingBytesAsString();
  WOLFSSL_CERT_MANAGER cm;
  wc_InitCertManager(&cm);
  wolfSSL_CertManagerLoadCA(&cm, const_cast<char*>(file.c_str()),
                           const_cast<char*>(path.c_str()));
  wc_FreeCertManager(&cm);
  return 0;
}