#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "disas/disas.h"
#include "target/mips/cpu.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct CPUMIPSState env;
  struct DisasContext ctx;

  // Initialize the CPUMIPSState and DisasContext structures
  memset(&env, 0, sizeof(env));
  memset(&ctx, 0, sizeof(ctx));

  // Consume data for the DisasContext structure
  ctx.pc = stream.ConsumeIntegral<uint32_t>();
  ctx.delayed_pc = stream.ConsumeIntegral<uint32_t>();
  ctx.delayed_inst = stream.ConsumeBool();
  ctx.bstate = static_cast<DisasBState>(stream.ConsumeIntegralInRange<int>(0, 2));
  ctx.cp0_gcr_base = stream.ConsumeIntegral<uint64_t>();
  ctx.hflags = stream.ConsumeIntegral<uint32_t>();
  ctx.isa = stream.ConsumeIntegral<uint32_t>();
  ctx.micromips = stream.ConsumeBool();

  // Call the function to fuzz
  decode_micromips32_opc(&env, &ctx);

  return 0;
}