#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include <wolfssl/options.h>
#include <wolfssl/ssl.h>
#include <wolfssl/wolfcrypt/asn.h>
#include <wolfssl/wolfcrypt/asn_public.h>
#include <wolfssl/wolfcrypt/cert.h>
#include <wolfssl/wolfcrypt/sha.h>
#include <wolfssl/wolfcrypt/sha256.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t cert_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::vector<uint8_t> cert_data =
      stream.ConsumeBytes<uint8_t>(cert_size);
  const int flags = stream.ConsumeIntegral<int>();

  struct WOLFSSL_CERT_MANAGER cert_manager;
  wolfSSL_CERT_MANAGER_init(&cert_manager);

  int ret = wolfSSL_CertManagerLoadCABuffer(&cert_manager,
                                           reinterpret_cast<char*>(const_cast<uint8_t*>(cert_data.data())),
                                           cert_data.size(), flags);
  if (ret == WOLFSSL_SUCCESS) {
    wolfSSL_CERT_MANAGER_free(&cert_manager);
  }

  return 0;
}

// Add the main function to allow running the program as a standalone application
int main() {
  // Generate a random input
  FuzzedDataProvider stream(1024);
  const size_t cert_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const std::vector<uint8_t> cert_data =
      stream.ConsumeBytes<uint8_t>(cert_size);
  const int flags = stream.ConsumeIntegral<int>();

  // Initialize the certificate manager
  struct WOLFSSL_CERT_MANAGER cert_manager;
  wolfSSL_CERT_MANAGER_init(&cert_manager);

  // Load the certificate into the manager
  int ret = wolfSSL_CertManagerLoadCABuffer(&cert_manager,
                                           reinterpret_cast<char*>(const_cast<uint8_t*>(cert_data.data())),
                                           cert_data.size(), flags);

  // Free the certificate manager
  if (ret == WOLFSSL_SUCCESS) {
    wolfSSL_CERT_MANAGER_free(&cert_manager);
  }

  return 0;
}