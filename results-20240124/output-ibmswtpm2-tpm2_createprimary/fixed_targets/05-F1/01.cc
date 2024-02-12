#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#ifdef TPM_WINDOWS
#include <windows.h>
#include <winsock.h>
#endif

extern "C" {
#include "Implementation.h"	/* kgold */
#include "TpmTcpProtocol.h"
#include "Manufacture_fp.h"
#include "Platform_fp.h"
#include "Simulator_fp.h"
#ifdef TPM_WINDOWS
#include "TcpServer_fp.h"
#endif
#ifdef TPM_POSIX
#include "TcpServerPosix_fp.h"
#endif
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct CreatePrimary_In in;
  struct CreatePrimary_Out out;

  if (Data == NULL || Size == 0) {
    return 0;
  }

  if (TPM2_CreatePrimary(&in, &out) != 0) {
    extern "C" {
      dprintf(STDERR_FILENO, "[FAILED] manufacturing\n");
    }
    exit(1);
  }

  return 0;
}