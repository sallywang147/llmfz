#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include "CryptSecret.h"
#include "Implementation.h"
#include "Manufacture_fp.h"
#include "Platform.h"
#include "Startup_fp.h"
#include "TpmBuildSwitches.h"
#include "_TPM_Init_fp.h"
#include "tpm_types.h"
}

const uint8_t STARTUP[] = {0x80, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x01, 0x44, 0x00, 0x00};

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
  ::ExecuteCommand(sizeof(STARTUP), (uint8_t *)STARTUP, &response_size, &response);

  /* Issue fuzzed command. */
  TPM2B_DATA data_tpm;
  data_tpm.t.size = size;
  memcpy(data_tpm.t.buffer, data, size);

  TPM2B_PUBLIC_KEY_RSA secret_tpm;
  secret_tpm.t.size = 0;

  ::CryptSecretEncrypt(0, NULL, &data_tpm, &secret_tpm);
  return 0; /* Non-zero return values are reserved for future use. */
}