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

  SensitiveToDuplicate(&sensitive, &name, parentHandle, nameAlg, &seed, &symDef,
                       &innerSymKey, &outPrivate);
  return 0;
}