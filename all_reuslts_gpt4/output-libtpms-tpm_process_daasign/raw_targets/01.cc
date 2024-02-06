#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "tpm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct tdTPM_STATE tpm_state;
  struct tdTPM_STORE_BUFFER response;
  struct tdTPM_TRANSPORT_INTERNAL transportInternal;

  // Initialize the structures
  TPM_STATE_Init(&tpm_state);
  TPM_STORE_BUFFER_Init(&response);
  TPM_TRANSPORT_INTERNAL_Init(&transportInternal);

  // Consume data for the parameters
  short tag = stream.ConsumeIntegral<short>();
  int paramSize = stream.ConsumeIntegral<int>();
  int ordinal = stream.ConsumeIntegral<int>();
  
  // Generate command string
  std::string commandStr = stream.ConsumeRemainingBytesAsString();
  char *command = const_cast<char*>(commandStr.c_str());

  // Call the function to be fuzzed
  TPM_Process_DAASign(&tpm_state, &response, tag, paramSize, ordinal, command, &transportInternal);

  // Cleanup
  TPM_STATE_Delete(&tpm_state);
  TPM_STORE_BUFFER_Delete(&response);
  TPM_TRANSPORT_INTERNAL_Delete(&transportInternal);

  return 0;
}