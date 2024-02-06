#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "TPM2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize parameters for SensitiveToDuplicate
  TPMT_SENSITIVE sensitive;
  TPM2B_NAME name;
  int parentHandle = stream.ConsumeIntegral<int>();
  short nameAlg = stream.ConsumeIntegral<short>();
  TPM2B_SEED seed;
  TPMT_SYM_DEF_OBJECT symDef;
  TPM2B_DATA innerSymKey;
  TPM2B_PRIVATE outPrivate;

  // Consume data for sensitive
  sensitive.sensitiveArea.sensitiveType = stream.ConsumeIntegral<TPM_ALG_ID>();
  sensitive.sensitiveArea.authValue.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(sensitive.sensitiveArea.authValue.t.buffer));
  stream.ConsumeData(sensitive.sensitiveArea.authValue.t.buffer, sensitive.sensitiveArea.authValue.t.size);

  // Consume data for name
  name.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(name.t.name));
  stream.ConsumeData(name.t.name, name.t.size);

  // Consume data for seed
  seed.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(seed.t.buffer));
  stream.ConsumeData(seed.t.buffer, seed.t.size);

  // Consume data for symDef
  symDef.algorithm = stream.ConsumeIntegral<TPM_ALG_ID>();
  symDef.keyBits.sym = stream.ConsumeIntegral<uint16_t>();
  symDef.mode.sym = stream.ConsumeIntegral<TPM_ALG_ID>();

  // Consume data for innerSymKey
  innerSymKey.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(innerSymKey.t.buffer));
  stream.ConsumeData(innerSymKey.t.buffer, innerSymKey.t.size);

  // Call the function to fuzz
  SensitiveToDuplicate(&sensitive, &name, parentHandle, nameAlg, &seed, &symDef, &innerSymKey, &outPrivate);

  return 0;
}