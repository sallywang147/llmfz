#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "TPM2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the structures
  union.TPM2B_DIGEST secret = {};
  union.TPM2B_NAME name = {};
  union.TPM2B_SEED seed = {};
  union.TPM2B_ID_OBJECT outIDObject = {};

  // Consume data for secret
  size_t secret_size = stream.ConsumeIntegralInRange<size_t>(0, sizeof(secret.t.buffer));
  std::vector<uint8_t> secret_buffer = stream.ConsumeBytes<uint8_t>(secret_size);
  secret.t.size = secret_size;
  memcpy(secret.t.buffer, secret_buffer.data(), secret_size);

  // Consume data for name
  size_t name_size = stream.ConsumeIntegralInRange<size_t>(0, sizeof(name.t.name));
  std::vector<uint8_t> name_buffer = stream.ConsumeBytes<uint8_t>(name_size);
  name.t.size = name_size;
  memcpy(name.t.name, name_buffer.data(), name_size);

  // Consume data for seed
  size_t seed_size = stream.ConsumeIntegralInRange<size_t>(0, sizeof(seed.t.buffer));
  std::vector<uint8_t> seed_buffer = stream.ConsumeBytes<uint8_t>(seed_size);
  seed.t.size = seed_size;
  memcpy(seed.t.buffer, seed_buffer.data(), seed_size);

  // Consume data for protector
  int protector = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  SecretToCredential(&secret, &name, &seed, protector, &outIDObject);

  return 0;
}