#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "TPM2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for SecretToCredential
  TPM2B_DIGEST secret;
  TPM2B_NAME name;
  TPM2B_SEED seed;
  TPM2B_ID_OBJECT outIDObject;

  // Consume data for the parameters from the fuzzing input
  secret.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(secret.buffer));
  std::vector<uint8_t> secret_buffer = stream.ConsumeBytes<uint8_t>(secret.size);
  memcpy(secret.buffer, secret_buffer.data(), secret.size);

  name.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(name.name));
  std::vector<uint8_t> name_buffer = stream.ConsumeBytes<uint8_t>(name.size);
  memcpy(name.name, name_buffer.data(), name.size);

  seed.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(seed.buffer));
  std::vector<uint8_t> seed_buffer = stream.ConsumeBytes<uint8_t>(seed.size);
  memcpy(seed.buffer, seed_buffer.data(), seed.size);

  int protector = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  SecretToCredential(&secret, &name, &seed, protector, &outIDObject);

  return 0;
}