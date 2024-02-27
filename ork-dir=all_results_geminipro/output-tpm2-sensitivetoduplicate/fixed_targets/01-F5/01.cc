#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "TPM2B_DATA.h"
#include "TPM2B_NAME.h"
#include "TPM2B_PRIVATE.h"
#include "TPM2B_SEED.h"
#include "TPMT_SENSITIVE.h"
#include "TPMT_SYM_DEF_OBJECT.h"

extern "C" {
#include "TPM2_Import.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  TPMT_SENSITIVE sensitive;
  memset(&sensitive, 0, sizeof(sensitive));
  TPM2B_NAME name;
  memset(&name, 0, sizeof(name));
  int parentHandle = stream.ConsumeIntegral<int>();
  short nameAlg = stream.ConsumeIntegral<short>();
  TPM2B_SEED seed;
  memset(&seed, 0, sizeof(seed));
  TPMT_SYM_DEF_OBJECT symDef;
  memset(&symDef, 0, sizeof(symDef));
  TPM2B_DATA innerSymKey;
  memset(&innerSymKey, 0, sizeof(innerSymKey));
  TPM2B_PRIVATE outPrivate;
  memset(&outPrivate, 0, sizeof(outPrivate));

  // Fix the function call to use the correct function name
  TPM2_SensitiveToDuplicate(&sensitive, &name, parentHandle, nameAlg, &seed, &symDef,
                       &innerSymKey, &outPrivate);
  return 0;
}
```

The original code has a typo in the function call: `SensitiveToDuplicate` instead of `TPM2_SensitiveToDuplicate`. This typo caused the linker to fail to find the function definition. The corrected code uses the correct function name, which should resolve the build error.