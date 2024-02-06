#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "argon2.h"

extern "C" {
#include "argon2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  argon2_context context;
  argon2_instance_t instance;
  argon2_context_init(&context);
  argon2_instance_init(&instance);
  instance.output = (uint8_t*)malloc(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  instance.output_len = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  instance.salt = (uint8_t*)malloc(stream.ConsumeIntegralInRange<size_t>(1, 1024));
  instance.salt_len = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  instance.memory_cost = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  instance.parallelism = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  instance.time_cost = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  instance.type = stream.ConsumeIntegralInRange<argon2_type>(Argon2_d, Argon2_id);
  instance.version = stream.ConsumeIntegralInRange<uint32_t>(0x10, 0x19);
  instance.lanes = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  instance.threads = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);

  // Generate a random password.
  size_t password_len = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  uint8_t* password = (uint8_t*)malloc(password_len);
  stream.ConsumeBytes<uint8_t>(password, password_len);

  // Hash the password.
  int result = argon2_hash(&instance, password, password_len, instance.salt, instance.salt_len, instance.output, instance.output_len, &context);
  if (result != ARGON2_OK) {
    // Password hashing failed.
    return 0;
  }

  // Verify the password.
  result = argon2_verify(&instance, password, password_len, instance.output, instance.output_len, &context);
  if (result != ARGON2_OK) {
    // Password verification failed.
  }

  argon2_finalize(&context, &instance);
  argon2_context_free(&context);
  argon2_instance_free(&instance);
  free(instance.output);
  free(instance.salt);
  free(password);

  return 0;
}