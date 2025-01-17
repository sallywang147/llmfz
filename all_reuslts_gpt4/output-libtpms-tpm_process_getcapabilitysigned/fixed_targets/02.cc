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

  short tag = stream.ConsumeIntegral<short>();
  int paramSize = stream.ConsumeIntegral<int>();
  int ordinal = stream.ConsumeIntegral<int>();

  std::string command = stream.ConsumeRandomLengthString();
  char *command_ptr = const_cast<char*>(command.c_str());

  TPM_Process_GetCapabilitySigned(&tpm_state, &response, tag, paramSize, ordinal, command_ptr, &transportInternal);

  return 0;
}