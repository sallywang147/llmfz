#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct TPMT_SENSITIVE sensitive = {};
  sensitive.sensitiveType = stream.ConsumeIntegral<uint8_t>();
  sensitive.authValue.size = stream.ConsumeIntegral<uint16_t>();
  stream.ConsumeBytes<uint8_t>(sensitive.authValue.buffer,
                               sensitive.authValue.size);

  union TPM2B_NAME name = {};
  name.size = stream.ConsumeIntegral<uint16_t>();
  stream.ConsumeBytes<uint8_t>(name.name, name.size);

  const int parentHandle = stream.ConsumeIntegral<int>();
  const short nameAlg = stream.ConsumeIntegral<short>();

  union TPM2B_SEED seed = {};
  seed.size = stream.ConsumeIntegral<uint16_t>();
  stream.ConsumeBytes<uint8_t>(seed.buffer, seed.size);

  struct TPMT_SYM_DEF_OBJECT symDef = {};
  symDef.algorithm = stream.ConsumeIntegral<uint16_t>();
  symDef.keyBits.aes = stream.ConsumeIntegral<uint16_t>();
  symDef.mode.aes = stream.ConsumeIntegral<uint16_t>();

  union TPM2B_DATA innerSymKey = {};
  innerSymKey.size = stream.ConsumeIntegral<uint16_t>();
  stream.ConsumeBytes<uint8_t>(innerSymKey.buffer, innerSymKey.size);

  union TPM2B_PRIVATE outPrivate = {};
  outPrivate.size = stream.ConsumeIntegral<uint16_t>();
  stream.ConsumeBytes<uint8_t>(outPrivate.buffer, outPrivate.size);

  SensitiveToDuplicate(&sensitive, &name, parentHandle, nameAlg, &seed, &symDef,
                      &innerSymKey, &outPrivate);
  return 0;
}