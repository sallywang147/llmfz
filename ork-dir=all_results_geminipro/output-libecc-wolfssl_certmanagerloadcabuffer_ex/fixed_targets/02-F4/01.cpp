#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include <wolfssl/options.h>
#include <wolfssl/ssl.h>

extern "C" {
#include <wolfssl/wolfcrypt/sha.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  wolfSSL_CTX* ctx = wolfSSL_CTX_new(wolfTLSv1_2_client_method());
  if (ctx == nullptr) {
    return 0;
  }

  wolfSSL_CERT_MANAGER* mgr = wolfSSL_CERT_MANAGER_new();
  if (mgr == nullptr) {
    wolfSSL_CTX_free(ctx);
    return 0;
  }

  const size_t cert_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  const char* cert_data = reinterpret_cast<const char*>(stream.ConsumeBytes<uint8_t>(cert_size).data());

  const int load_flags = stream.ConsumeIntegral<int>();
  const int check_time = stream.ConsumeIntegral<int>();
  const int check_depth = stream.ConsumeIntegral<int>();

  int ret = wolfSSL_CertManagerLoadCABuffer_ex(mgr, const_cast<char*>(cert_data), cert_size, load_flags, check_time, check_depth);
  if (ret != WOLFSSL_SUCCESS) {
    wolfSSL_CERT_MANAGER_free(mgr);
    wolfSSL_CTX_free(ctx);
    return 0;
  }

  wolfSSL_SetCertManager(ctx, mgr);
  wolfSSL_CERT_MANAGER_free(mgr); // Free the manager before freeing the context
  wolfSSL_CTX_free(ctx);
  return 0;
}
```

The issue in the original code was that `wolfSSL_CERT_MANAGER_free` was called after `wolfSSL_CTX_free`. This is incorrect because the manager is associated with the context, and freeing the context before freeing the manager results in undefined behavior.

The corrected code fixes this issue by calling `wolfSSL_CERT_MANAGER_free` before `wolfSSL_CTX_free`. This ensures that the manager is freed before the context, which is the correct order of operations.