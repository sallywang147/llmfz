#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {  // Wrap the header with 'extern "C"' to fix the linking issue.
#include <tpm/tpm_types.h>
}

int TPM_Process_DAASign(struct tdTPM_STATE * tpm_state, struct tdTPM_STORE_BUFFER * response, short tag, int paramSize, int ordinal, char * command, struct tdTPM_TRANSPORT_INTERNAL * transportInternal) {
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct tdTPM_STATE *tpm_state = (struct tdTPM_STATE *)stream.ConsumeBytes<uint8_t>(sizeof(struct tdTPM_STATE));
  struct tdTPM_STORE_BUFFER *response = (struct tdTPM_STORE_BUFFER *)stream.ConsumeBytes<uint8_t>(sizeof(struct tdTPM_STORE_BUFFER));
  short tag = stream.ConsumeIntegral<short>();
  int paramSize = stream.ConsumeIntegral<int>();
  int ordinal = stream.ConsumeIntegral<int>();
  char *command = (char *)stream.ConsumeBytes<uint8_t>(paramSize);
  struct tdTPM_TRANSPORT_INTERNAL *transportInternal = (struct tdTPM_TRANSPORT_INTERNAL *)stream.ConsumeBytes<uint8_t>(sizeof(struct tdTPM_TRANSPORT_INTERNAL));

  TPM_Process_DAASign(tpm_state, response, tag, paramSize, ordinal, command, transportInternal);

  return 0;
}