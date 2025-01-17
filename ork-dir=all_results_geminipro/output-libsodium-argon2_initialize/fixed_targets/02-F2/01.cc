#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "argon2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Argon2_instance_t instance;
  struct Argon2_Context context;

  argon2_context_init(&context);
  argon2_instance_init(&instance, &context);

  const uint32_t max_memory = stream.ConsumeIntegralInRange<uint32_t>(1, 1000000000);
  const uint32_t max_time = stream.ConsumeIntegralInRange<uint32_t>(1, 1000000000);
  const uint32_t parallelism = stream.ConsumeIntegralInRange<uint32_t>(1, 1000000000);
  const uint32_t hash_len = stream.ConsumeIntegralInRange<uint32_t>(1, 1000000000);
  const uint32_t salt_len = stream.ConsumeIntegralInRange<uint32_t>(1, 1000000000);
  const uint32_t secret_len = stream.ConsumeIntegralInRange<uint32_t>(1, 1000000000);

  instance.memory = max_memory;
  instance.time = max_time;
  instance.parallelism = parallelism;
  instance.hash_len = hash_len;
  instance.salt_len = salt_len;
  instance.secret_len = secret_len;

  const std::string password = stream.ConsumeRandomLengthString();
  const std::string salt = stream.ConsumeRandomLengthString();

  int ret = argon2_initialize(&instance, &context);
  if (ret != ARGON2_OK) {
    return 0;
  }

  ret = argon2_hash(
      &instance,
      reinterpret_cast<const uint8_t*>(password.c_str()), password.size(),
      reinterpret_cast<const uint8_t*>(salt.c_str()), salt.size(),
      nullptr, 0,
      nullptr, 0,
      nullptr, 0);
  if (ret != ARGON2_OK) {
    return 0;
  }

  argon2_context_free(&context);
  argon2_instance_free(&instance, &context);

  return 0;
}