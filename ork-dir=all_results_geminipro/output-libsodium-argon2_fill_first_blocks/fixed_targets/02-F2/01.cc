#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "argon2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t salt_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t password_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  const size_t hash_length = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  const uint32_t parallelism = provider.ConsumeIntegralInRange<uint32_t>(0, 1024);
  const uint32_t memory_cost = provider.ConsumeIntegralInRange<uint32_t>(0, 1024);
  const uint32_t iterations = provider.ConsumeIntegralInRange<uint32_t>(0, 1024);
  const uint32_t version = provider.ConsumeIntegralInRange<uint32_t>(0, 1024);
  const uint32_t type = provider.ConsumeIntegralInRange<uint32_t>(0, 1024);

  std::vector<uint8_t> salt = provider.ConsumeBytes<uint8_t>(salt_length);
  std::vector<uint8_t> password = provider.ConsumeBytes<uint8_t>(password_length);
  std::vector<uint8_t> hash(hash_length);

  Argon2_instance_t instance;
  instance.version = version;
  instance.type = type;
  instance.memory_cost = memory_cost;
  instance.iterations = iterations;
  instance.parallelism = parallelism;
  instance.lane_length = 0;
  instance.threads = 0;
  instance.flags = ARGON2_DEFAULT_FLAGS;
  instance.secret = password.data();
  instance.secret_len = password.size();
  instance.salt = salt.data();
  instance.salt_len = salt.size();
  instance.hash = hash.data();
  instance.hash_len = hash.size();

  argon2_fill_first_blocks((char *)hash.data(), &instance);

  return 0;
}