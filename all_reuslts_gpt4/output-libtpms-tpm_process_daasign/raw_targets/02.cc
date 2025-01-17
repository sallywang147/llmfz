#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "tpm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the TPM state
  struct tdTPM_STATE tpm_state;
  TPM_STATE_Init(&tpm_state);

  // Initialize the response buffer
  struct tdTPM_STORE_BUFFER response;
  TPM_Sbuffer_Init(&response);

  // Initialize the transport internal
  struct tdTPM_TRANSPORT_INTERNAL transportInternal;
  TPM_TransportInternal_Init(&transportInternal);

  // Consume data for the tag, paramSize and ordinal
  short tag = stream.ConsumeIntegral<short>();
  int paramSize = stream.ConsumeIntegral<int>();
  int ordinal = stream.ConsumeIntegral<int>();

  // Consume data for the command
  std::string command = stream.ConsumeRemainingBytesAsString();
  
  // Call the function to fuzz
  TPM_Process_DAASign(&tpm_state, &response, tag, paramSize, ordinal, const_cast<char*>(command.c_str()), &transportInternal);

  // Cleanup
  TPM_Sbuffer_Delete(&response);
  TPM_TransportInternal_Delete(&transportInternal);

  return 0;
}