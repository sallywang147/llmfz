#include <stdint.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "TpmBuildSwitches.h"
#include "CreatePrimary_fp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  if (size < sizeof(struct CreatePrimary_In) + sizeof(struct CreatePrimary_Out)) {
    return 0;
  }

  struct CreatePrimary_In in;
  struct CreatePrimary_Out out;

  stream.ConsumeData(&in, sizeof(struct CreatePrimary_In));
  stream.ConsumeData(&out, sizeof(struct CreatePrimary_Out));

  TPM2_CreatePrimary(&in, &out);

  return 0;
}