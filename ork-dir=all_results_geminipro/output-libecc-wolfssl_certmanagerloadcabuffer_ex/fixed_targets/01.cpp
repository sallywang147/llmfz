#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/cert.h>
#include <wolfssl/wolfcrypt/sha256.h>  // Include the missing header file

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct WOLFSSL_CERT_MANAGER* cert_manager =
      wolfSSL_CertManagerNew(wolfSSL_GetGlobalEnvironment());
  if (cert_manager == NULL) {
    return 0;
  }

  const std::vector<uint8_t> ca_buffer = stream.ConsumeRemainingBytes();
  const int ca_buffer_size = ca_buffer.size();
  const int flags = stream.ConsumeIntegral<int>();
  const int verify_depth = stream.ConsumeIntegral<int>();
  const int verify_hostname = stream.ConsumeIntegral<int>();

  int ret = wolfSSL_CertManagerLoadCABuffer_ex(
      cert_manager, reinterpret_cast<char*>(ca_buffer.data()), ca_buffer_size,
      flags, verify_depth, verify_hostname);

  wolfSSL_CertManagerFree(cert_manager);
  return ret;
}