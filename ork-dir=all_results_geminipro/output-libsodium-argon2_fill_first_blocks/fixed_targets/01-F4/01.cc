#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "argon2.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Argon2_Context context;
  memset(&context, 0, sizeof(Argon2_Context));

  context.outlen = stream.ConsumeIntegralInRange<uint32_t>(16, 1024);
  context.version = stream.ConsumeIntegralInRange<uint32_t>(0, 0x10);
  context.type = stream.ConsumeIntegralInRange<uint32_t>(0, 0x40);
  context.threads = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  context.lanes = stream.ConsumeIntegralInRange<uint32_t>(1, 1024);
  context.memory_cost = stream.ConsumeIntegralInRange<uint32_t>(1, 0x1000000);
  context.time_cost = stream.ConsumeIntegralInRange<uint32_t>(1, 0x1000000);

  const std::string password = stream.ConsumeRemainingBytesAsString();
  const std::string salt = stream.ConsumeRemainingBytesAsString();

  char blockhash[context.outlen];
  argon2_hash(&context, password.data(), password.length(), salt.data(), salt.length(), blockhash, context.outlen);

  return 0;
}