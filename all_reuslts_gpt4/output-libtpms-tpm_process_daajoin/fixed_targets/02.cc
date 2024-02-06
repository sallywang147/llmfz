#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tpm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct tdTPM_STATE tpm_state;
  struct tdTPM_STORE_BUFFER response;
  struct tdTPM_TRANSPORT_INTERNAL transportInternal;

  // Initialize the structures
  TPM_Init(&tpm_state);
  TPM_Sbuffer_Init(&response);
  TPM_TransportInternal_Init(&transportInternal);

  // Consume data for the parameters
  short tag = stream.ConsumeIntegral<short>();
  int paramSize = stream.ConsumeIntegral<int>();
  int ordinal = stream.ConsumeIntegral<int>();
  std::string command = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  TPM_Process_DAAJoin(&tpm_state, &response, tag, paramSize, ordinal, const_cast<char*>(command.c_str()), &transportInternal);

  // Cleanup
  TPM_Sbuffer_Delete(&response);
  TPM_TransportInternal_Delete(&transportInternal);

  return 0;
}