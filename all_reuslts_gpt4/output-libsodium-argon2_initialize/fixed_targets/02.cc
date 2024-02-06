#include <fuzzer/FuzzedDataProvider.h>
#include <argon2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Argon2_Context context;
  Argon2_instance_t instance;

  context.out = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2).data();
  context.outlen = stream.ConsumeIntegral<uint32_t>();
  context.pwd = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2).data();
  context.pwdlen = stream.ConsumeIntegral<uint32_t>();
  context.salt = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2).data();
  context.saltlen = stream.ConsumeIntegral<uint32_t>();
  context.secret = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2).data();
  context.secretlen = stream.ConsumeIntegral<uint32_t>();
  context.ad = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2).data();
  context.adlen = stream.ConsumeIntegral<uint32_t>();
  context.t_cost = stream.ConsumeIntegral<uint32_t>();
  context.m_cost = stream.ConsumeIntegral<uint32_t>();
  context.lanes = stream.ConsumeIntegral<uint32_t>();
  context.threads = stream.ConsumeIntegral<uint32_t>();
  context.version = stream.ConsumeIntegral<uint32_t>();
  context.allocate_cbk = NULL;
  context.free_cbk = NULL;
  context.flags = stream.ConsumeIntegral<uint32_t>();

  argon2_initialize(&instance, &context);

  return 0;
}