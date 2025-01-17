 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "TPM2_CreatePrimary.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct CreatePrimary_In in = {};
  struct CreatePrimary_Out out = {};
  in.primaryHandle = provider.ConsumeIntegral<uint32_t>();
  in.inSensitive = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegral<uint32_t>());
  in.inPublic = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegral<uint32_t>());
  TPM2_CreatePrimary(&in, &out);
  return 0;
}