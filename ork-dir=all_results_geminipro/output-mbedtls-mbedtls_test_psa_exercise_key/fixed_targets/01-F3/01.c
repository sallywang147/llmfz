#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

#include "mbedtls/psa_crypto.h"

extern "C" {
#include "mbedtls/psa_crypto_test.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int key = stream.ConsumeIntegral<int>();
  const int usage = stream.ConsumeIntegral<int>();
  const int alg = stream.ConsumeIntegral<int>();

  mbedtls_test_psa_exercise_key(key, usage, alg);
  return 0;
}
```

The original code has the following issues:

1. The `mbedtls/psa_crypto_test.h` header is not wrapped with `extern "C" {}`. This is necessary because the header contains C++ code, which is not compatible with C code.

2. The `mbedtls_test_psa_exercise_key` function is not declared as `extern "C"`, which is necessary because it is called from C code.

The fixed code addresses these issues by wrapping the `mbedtls/psa_crypto_test.h` header with `extern "C" {}` and declaring the `mbedtls_test_psa_exercise_key` function as `extern "C"`.