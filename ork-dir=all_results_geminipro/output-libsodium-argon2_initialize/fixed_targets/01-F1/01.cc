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