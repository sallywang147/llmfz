#include <stddef.h>
#include "Tpm.h"

extern "C" {
#include "fuzzer.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  CreatePrimary_In in;
  CreatePrimary_Out out;

  TPM2_CreatePrimary(&in, &out);

  return 0;
}