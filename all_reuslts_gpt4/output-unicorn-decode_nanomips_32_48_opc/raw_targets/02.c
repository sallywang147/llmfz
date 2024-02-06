#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "disas/disas.h"
#include "target/mips/cpu.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the CPUMIPSState and DisasContext objects.
  CPUMIPSState env;
  DisasContext ctx;

  // Clear the memory for both objects.
  memset(&env, 0, sizeof(env));
  memset(&ctx, 0, sizeof(ctx));

  // Consume data for the DisasContext object.
  ctx.pc = stream.ConsumeIntegral<uint32_t>();
  ctx.delayed_pc = stream.ConsumeIntegral<uint32_t>();
  ctx.delayed_inst = stream.ConsumeIntegral<uint32_t>();
  ctx.bstate = static_cast<DisasBranchType>(stream.ConsumeIntegralInRange<int>(0, DISAS_BRANCH_MAX - 1));
  ctx.hflags = stream.ConsumeIntegral<uint32_t>();

  // Call the function under test.
  decode_nanomips_32_48_opc(&env, &ctx);

  return 0;
}