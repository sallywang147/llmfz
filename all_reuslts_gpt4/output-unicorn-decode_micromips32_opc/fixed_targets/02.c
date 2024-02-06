#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "cpu.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the CPUMIPSState
  CPUMIPSState env;
  memset(&env, 0, sizeof(env));

  // Initialize the DisasContext
  DisasContext ctx;
  memset(&ctx, 0, sizeof(ctx));

  // Consume data for the DisasContext
  ctx.pc = stream.ConsumeIntegral<uint32_t>();
  ctx.delayed_pc = stream.ConsumeIntegral<uint32_t>();
  ctx.delayed_inst = stream.ConsumeBool();
  ctx.bstate = stream.ConsumeEnum<DisasBState>();
  ctx.cp0_gcr_base = stream.ConsumeIntegral<uint64_t>();
  ctx.hflags = stream.ConsumeIntegral<int32_t>();

  // Call the function to fuzz
  decode_micromips32_opc(&env, &ctx);

  return 0;
}