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
  TPM_RESULT res;
  struct tdTPM_STATE tpm_state;
  struct tdTPM_STORE_BUFFER response;
  short tag = 0;
  int paramSize = 0;
  int ordinal = 0;
  char *command = NULL;
  struct tdTPM_TRANSPORT_INTERNAL transportInternal;

  // Initialize the TPM state and transport internal structures.
  res = TPM_DAA_Init(&tpm_state, &transportInternal);
  if (res != TPM_SUCCESS) {
    printf("TPM_DAA_Init failed with error code %d\n", res);
    return -1;
  }

  // Process the DAAJoin command.
  res = TPM_Process_DAAJoin(&tpm_state, &response, tag, paramSize, ordinal, command,
                      &transportInternal);
  if (res != TPM_SUCCESS) {
    printf("TPM_Process_DAAJoin failed with error code %d\n", res);
    return -1;
  }

  // Clean up the TPM state and transport internal structures.
  TPM_DAA_Delete(&tpm_state);

  return 0;
}