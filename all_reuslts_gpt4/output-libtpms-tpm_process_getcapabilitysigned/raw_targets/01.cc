#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "tpm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct tdTPM_STATE tpm_state;
  struct tdTPM_STORE_BUFFER response;
  struct tdTPM_TRANSPORT_INTERNAL transportInternal;

  short tag = stream.ConsumeIntegral<short>();
  int paramSize = stream.ConsumeIntegral<int>();
  int ordinal = stream.ConsumeIntegral<int>();

  std::string command_str = stream.ConsumeRemainingBytesAsString();
  char* command = const_cast<char*>(command_str.c_str());

  TPM_Process_GetCapabilitySigned(&tpm_state, &response, tag, paramSize, ordinal, command, &transportInternal);

  return 0;
}