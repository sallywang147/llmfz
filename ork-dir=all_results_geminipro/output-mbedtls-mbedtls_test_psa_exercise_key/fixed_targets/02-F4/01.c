#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "mbedtls/psa.h"

extern "C" {
#include "mbedtls/psa_crypto.h"
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

The corrected code should now compile and run without errors.