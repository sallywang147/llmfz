#include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "tpm2_fuzz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct CreatePrimary_In in;
  memset(&in, 0, sizeof(in));
  in.primaryHandle = stream.ConsumeIntegral<uint32_t>();
  in.inSensitive = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  in.inPublic = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  in.outsideInfo = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  in.creationPCR = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  struct CreatePrimary_Out out;
  memset(&out, 0, sizeof(out));
  TPM2_CreatePrimary(&in, &out);
  return 0;
}