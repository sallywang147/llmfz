#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "argon2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Argon2_Context context;
  argon2_context_init(&context);

  // Set the Argon2 version, memory cost, parallelism, and hash length.
  context.version = ARGON2_VERSION_13;
  context.m_cost = stream.ConsumeIntegralInRange(1, 1 << 16);
  context.t_cost = stream.ConsumeIntegralInRange(1, 1 << 16);
  context.lanes = stream.ConsumeIntegralInRange(1, 1 << 16);
  context.hash_len = stream.ConsumeIntegralInRange(1, 1 << 16);

  // Set the password and salt.
  std::string password = stream.ConsumeRemainingBytesAsString();

  // Initialize the Argon2 instance.
  Argon2_Instance instance;
  argon2_instance_init(&instance, &context);

  // Hash the password.
  argon2_hash(&instance, password.data(), password.size(), NULL, 0, NULL, 0, NULL);

  // Destroy the Argon2 instance.
  argon2_instance_free(&instance, ARGON2_FREE_ARGON2_INSTANCE);

  // Destroy the Argon2 context.
  argon2_context_free(&context);

  return 0;
}