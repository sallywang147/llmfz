#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "wolfssl/options.h"
#include "wolfssl/ssl.h"

extern "C" {
#include "wolfssl/wolfcrypt/sha256.h"
#include "wolfssl/wolfcrypt/sha512.h"
#include "wolfssl/wolfcrypt/sha384.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  WOLFSSL_CERT_MANAGER* cert_manager = wolfSSL_CertManagerNew();
  if (cert_manager == nullptr) {
    return 0;
  }

  const std::string cert_file = stream.ConsumeRemainingBytesAsString();
  const std::string key_file = stream.ConsumeRemainingBytesAsString();

  wolfSSL_CertManagerLoadCA(cert_manager, cert_file.c_str(), key_file.c_str());
  wolfSSL_CertManagerFree(cert_manager);
  return 0;
}
```

The issue was that the `wolfSSL_CertManagerLoadCA` function expects `char*` arguments, but the `cert_file` and `key_file` variables were of type `std::string`. To fix this, the `c_str()` method was used to convert the `std::string` variables to `char*` arrays.