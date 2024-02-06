#include <fuzzer/FuzzedDataProvider.h>
#include <argon2.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize context and instance
  Argon2_Context context;
  Argon2_instance_t instance;

  // Consume data for context
  context.out = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.outlen = stream.ConsumeIntegral<uint32_t>();
  context.pwd = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.pwdlen = stream.ConsumeIntegral<uint32_t>();
  context.salt = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.saltlen = stream.ConsumeIntegral<uint32_t>();
  context.secret = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.secretlen = stream.ConsumeIntegral<uint32_t>();
  context.ad = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size)).data();
  context.adlen = stream.ConsumeIntegral<uint32_t>();
  context.t_cost = stream.ConsumeIntegral<uint32_t>();
  context.m_cost = stream.ConsumeIntegral<uint32_t>();
  context.lanes = stream.ConsumeIntegral<uint32_t>();
  context.threads = stream.ConsumeIntegral<uint32_t>();
  context.version = stream.ConsumeIntegral<uint32_t>();
  context.allocate_cbk = NULL;
  context.free_cbk = NULL;
  context.flags = stream.ConsumeIntegral<uint32_t>();

  // Consume data for instance
  instance.version = stream.ConsumeIntegral<uint32_t>();
  instance.memory = NULL;
  instance.passes = stream.ConsumeIntegral<uint32_t>();
  instance.memory_blocks = stream.ConsumeIntegral<uint32_t>();
  instance.segment_length = stream.ConsumeIntegral<uint32_t>();
  instance.lane_length = stream.ConsumeIntegral<uint32_t>();
  instance.lanes = stream.ConsumeIntegral<uint32_t>();
  instance.threads = stream.ConsumeIntegral<uint32_t>();

  // Call the function to fuzz
  argon2_finalize(&context, &instance);

  return 0;
}