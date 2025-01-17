#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "TPM2.h" // Assuming this is the header file where the function and its parameters are defined.

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  TPMT_SENSITIVE sensitive;
  TPM2B_NAME name;
  int parentHandle = stream.ConsumeIntegral<int>();
  short nameAlg = stream.ConsumeIntegral<short>();
  TPM2B_SEED seed;
  TPMT_SYM_DEF_OBJECT symDef;
  TPM2B_DATA innerSymKey;
  TPM2B_PRIVATE outPrivate;

  // Consume data for the sensitive structure
  if (stream.remaining_bytes() < sizeof(TPMT_SENSITIVE)) return 0;
  stream.ConsumeData(&sensitive, sizeof(TPMT_SENSITIVE));

  // Consume data for the name union
  if (stream.remaining_bytes() < sizeof(TPM2B_NAME)) return 0;
  stream.ConsumeData(&name, sizeof(TPM2B_NAME));

  // Consume data for the seed union
  if (stream.remaining_bytes() < sizeof(TPM2B_SEED)) return 0;
  stream.ConsumeData(&seed, sizeof(TPM2B_SEED));

  // Consume data for the symDef structure
  if (stream.remaining_bytes() < sizeof(TPMT_SYM_DEF_OBJECT)) return 0;
  stream.ConsumeData(&symDef, sizeof(TPMT_SYM_DEF_OBJECT));

  // Consume data for the innerSymKey union
  if (stream.remaining_bytes() < sizeof(TPM2B_DATA)) return 0;
  stream.ConsumeData(&innerSymKey, sizeof(TPM2B_DATA));

  // Consume data for the outPrivate union
  if (stream.remaining_bytes() < sizeof(TPM2B_PRIVATE)) return 0;
  stream.ConsumeData(&outPrivate, sizeof(TPM2B_PRIVATE));

  SensitiveToDuplicate(&sensitive, &name, parentHandle, nameAlg, &seed, &symDef, &innerSymKey, &outPrivate);

  return 0;
}