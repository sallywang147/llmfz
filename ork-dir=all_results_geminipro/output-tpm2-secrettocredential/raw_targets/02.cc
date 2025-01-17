#include <stddef.h>
#include <stdint.h>

extern "C" {
#include "Tpm.h"
#include "tpm_types.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TPM2B_DIGEST secret;
  secret.size = size;
  memcpy(secret.buffer, data, size);

  TPM2B_NAME name;
  name.size = 0;

  TPM2B_SEED seed;
  seed.size = 0;

  TPM2B_ID_OBJECT outIDObject;
  outIDObject.size = 0;

  SecretToCredential(&secret, &name, &seed, 0, &outIDObject);
  return 0;
}