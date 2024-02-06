#include <fuzzer/FuzzedDataProvider.h>
#include <argon2.h>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create and initialize Argon2_Context
  Argon2_Context context;
  context.out = nullptr;
  context.outlen = stream.ConsumeIntegral<uint32_t>();
  context.pwd = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.pwdlen = stream.ConsumeIntegral<uint32_t>();
  context.salt = (uint8_t*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.saltlen = stream.ConsumeIntegral<uint32_t>();
  context.secret = nullptr;
  context.secretlen = 0;
  context.ad = nullptr;
  context.adlen = 0;
  context.t_cost = stream.ConsumeIntegral<uint32_t>();
  context.m_cost = stream.ConsumeIntegral<uint32_t>();
  context.lanes = stream.ConsumeIntegral<uint32_t>();
  context.threads = stream.ConsumeIntegral<uint32_t>();
  context.version = ARGON2_VERSION_13;
  context.allocate_cbk = nullptr;
  context.free_cbk = nullptr;
  context.flags = ARGON2_DEFAULT_FLAGS;

  // Create and initialize Argon2_instance_t
  Argon2_instance_t instance;
  instance.context_ptr = &context;

  // Call the function to fuzz
  argon2_initialize(&instance, &context);

  return 0;
}