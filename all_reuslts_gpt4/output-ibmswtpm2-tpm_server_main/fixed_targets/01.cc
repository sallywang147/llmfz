#include <stdint.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "TpmBuildSwitches.h"
#include "TpmTcpProtocol.h"
#ifdef TPM_WINDOWS
#include "TcpServer_fp.h"
#endif
#ifdef TPM_POSIX
#include "TcpServerPosix_fp.h"
#endif
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (data == NULL || size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int argc = stream.ConsumeIntegralInRange(1, 10);
  char **argv = (char **)malloc(sizeof(char *) * argc);

  for (int i = 0; i < argc; i++) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv[i] = strdup(arg.c_str());
  }

  tpm_server_main(argc, argv);

  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }

  free(argv);

  return 0;
}