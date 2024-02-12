#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "TpmBuildSwitches.h"
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

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  int PortNumber = 0;
  int PortNumberPlatform = 0;

  if (Data == NULL || Size == 0) {
    return 0;
  }

  _plat__NVEnable(NULL);
  if (TPM_Manufacture(1) != 0) {
    dprintf(STDERR_FILENO, "[FAILED] manufacturing\n");
    exit(1);
  }
  // Coverage test - repeated manufacturing attempt
  if (TPM_Manufacture(0) != 1) {
    dprintf(STDERR_FILENO, "[FAILED] Coverage test - repeated manufacturing attempt\n");
    exit(2);
  }
  // Coverage test - re-manufacturing
  TPM_TearDown();
  if (TPM_Manufacture(1) != 0) {
    dprintf(STDERR_FILENO, "[FAILED] Coverage test - re-manufacturing\n");
    exit(3);
  }
  // Disable NV memory
  _plat__NVDisable();
  /* power on the TPM kgold MS simulator comes up powered off */
  _rpc__Signal_PowerOn(FALSE);
  _rpc__Signal_NvOn();

  // From TSS2 MSSIM simulator_setup
  // tcti_platform_command (tctiContext, MS_SIM_POWER_ON);
  _rpc__Signal_PowerOn(FALSE);
  // tcti_platform_command (tctiContext, MS_SIM_NV_ON);
  _rpc__Signal_NvOn();

  StartTcpServer(&PortNumber, &PortNumberPlatform);

  return 0;
}