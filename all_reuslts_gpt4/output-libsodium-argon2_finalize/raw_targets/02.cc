#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "argon2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Argon2_Context
  Argon2_Context context;
  context.out = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.outlen = stream.ConsumeIntegral<uint32_t>();
  context.pwd = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.pwdlen = stream.ConsumeIntegral<uint32_t>();
  context.salt = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.saltlen = stream.ConsumeIntegral<uint32_t>();
  context.secret = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.secretlen = stream.ConsumeIntegral<uint32_t>();
  context.ad = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.adlen = stream.ConsumeIntegral<uint32_t>();
  context.t_cost = stream.ConsumeIntegral<uint32_t>();
  context.m_cost = stream.ConsumeIntegral<uint32_t>();
  context.lanes = stream.ConsumeIntegral<uint32_t>();
  context.threads = stream.ConsumeIntegral<uint32_t>();
  context.version = stream.ConsumeIntegral<uint32_t>();
  context.allocate_cbk = nullptr;
  context.free_cbk = nullptr;
  context.flags = stream.ConsumeIntegral<uint32_t>();

  // Initialize Argon2_instance_t
  Argon2_instance_t instance;
  instance.context = &context;

  // Call the function to fuzz
  argon2_finalize(&context, &instance);

  return 0;
}