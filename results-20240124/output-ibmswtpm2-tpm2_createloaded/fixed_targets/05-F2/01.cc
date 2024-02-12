#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Tpm.h"

extern "C" {
#include "TpmTypes.h"
#include "CreateLoaded_fp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Data == NULL || Size == 0) {
    return 0;
  }

  CreateLoaded_In in;
  CreateLoaded_Out out;

  if (TPM2_CreateLoaded(&in, &out) != 0) {
    return 0;
  }

  return 0;
}