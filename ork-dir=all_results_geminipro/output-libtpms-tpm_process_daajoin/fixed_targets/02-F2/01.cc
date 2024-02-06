#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libtpms/tpm_error.h>
#include <libtpms/tpm_library.h>

extern "C" {
#include <libtpms/tpm_daa.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct tdTPM_STATE tpm_state;
  struct tdTPM_STORE_BUFFER response;
  short tag = 0;
  int paramSize = 0;
  int ordinal = 0;
  char *command = NULL;
  struct tdTPM_TRANSPORT_INTERNAL transportInternal;

  TPM_Process_DAAJoin(&tpm_state, &response, tag, paramSize, ordinal, command,
                      &transportInternal);

  return 0;
}