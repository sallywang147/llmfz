#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "mbedtls/psa.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int key = stream.ConsumeIntegral<int>();
  const int usage = stream.ConsumeIntegral<int>();
  const int alg = stream.ConsumeIntegral<int>();

  mbedtls_test_psa_exercise_key(key, usage, alg);
  return 0;
}
```

The error message is:

```
error: undefined reference to `mbedtls_test_psa_exercise_key'
```

This means that the linker cannot find the definition of the function `mbedtls_test_psa_exercise_key`. To fix this, we need to make sure that the header file that declares the function is included in the compilation.

In this case, the header file is `mbedtls/psa.h`. We can include it by adding the following line to the top of the file:

```c++
#include "mbedtls/psa.h"
```

After adding this line, the code should compile and run without errors.