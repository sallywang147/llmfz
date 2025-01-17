#include <stddef.h>
#include <stdint.h>

extern "C" {
#include "Capabilities.h"
#include "ExecCommand_fp.h"
#include "Implementation.h"
#include "Manufacture_fp.h"
#include "Platform.h"
#include "Startup_fp.h"
#include "TpmBuildSwitches.h"
#include "_TPM_Init_fp.h"
#include "tpm_types.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  uint8_t *response;
  unsigned response_size;

  /* Initialize TPM state. */
  _plat__Signal_PowerOn();
  _plat__NVEnable(NULL);
  assert(TPM_Manufacture(1) == 0);
  _plat__NVDisable();
  _TPM_Init();
  _plat__SetNvAvail();
  _plat__Signal_PhysicalPresenceOn();

  /* Issue the TPM2_Startup command. */
  const uint8_t STARTUP[] = {0x80, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x01, 0x44, 0x00, 0x00};
  ::ExecuteCommand(sizeof(STARTUP), (uint8_t *)STARTUP, &response_size, &response);

  /* Fuzzed command. */
  union.TPM2B_DIGEST secret;
  union.TPM2B_NAME name;
  union.TPM2B_SEED seed;
  union.TPM2B_ID_OBJECT outIDObject;

  ::SecretToCredential(&secret, &name, &seed, 0, &outIDObject);

  return 0; /* Non-zero return values are reserved for future use. */
}