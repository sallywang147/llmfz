#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "wolfssl/options.h"
#include "wolfssl/wolfssl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct WOLFSSL_CERT_MANAGER* manager = wolfSSL_CertManagerNew();
  const size_t cert_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::vector<uint8_t> cert_buffer =
      stream.ConsumeBytes<uint8_t>(cert_size);
  const int flags = stream.ConsumeIntegral<int>();
  wolfSSL_CertManagerLoadCABuffer(manager,
                                 reinterpret_cast<char*>(const_cast<uint8_t*>(
                                     cert_buffer.data())),
                                 cert_size, flags);
  wolfSSL_CertManagerFree(manager);
  return 0;
}