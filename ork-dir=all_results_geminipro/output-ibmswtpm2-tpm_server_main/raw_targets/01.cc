#include <stdio.h>
#include <stdlib.h>

#include "TpmBuildSwitches.h"
#include "TpmTcpProtocol.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  int argc = 3;
  char *argv[] = {
      "tpm_server_main",
      "-h",
      "127.0.0.1",
  };

  if (size > 0) {
    argv[2] = (char *)data;
  }

  return tpm_server_main(argc, argv);
}