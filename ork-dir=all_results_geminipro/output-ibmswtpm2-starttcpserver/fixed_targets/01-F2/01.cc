#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "TpmBuildSwitches.h"
#include "TpmTcpProtocol.h"
#include "TcpServer.h"
#ifdef TPM_WINDOWS
#include "TcpServer_fp.h"
#endif
#ifdef TPM_POSIX
#include "TcpServerPosix_fp.h"
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  int PortNumber = 0;
  int PortNumberPlatform = 0;

  if (Data == NULL || Size == 0) {
    return 0;
  }

  StartTcpServer(&PortNumber, &PortNumberPlatform);

  std::vector<uint8_t> input_buffer(Data, Data + Size);

  while (!input_buffer.empty()) {
    size_t next_size = input_buffer.size();
    if (next_size > 1024) {
      next_size = 1024;
    }
    auto next_input = input_buffer.data();
    input_buffer.erase(input_buffer.begin(),
                       input_buffer.begin() + next_size);

    TpmTcpProtocol_ReceiveBytes(next_input, next_size);
  }

  TpmTcpProtocol_Close();

  return 0;
}