#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cpu.h"
#include "exec/exec-all.h"
#include "exec/cpu_ldst.h"
#include "disas/disas.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(CPUMIPSState) + sizeof(DisasContext)) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  CPUMIPSState env;
  memset(&env, 0, sizeof(env));
  DisasContext ctx;
  memset(&ctx, 0, sizeof(ctx));

  // Consume data for CPUMIPSState and DisasContext from the fuzzer input
  fuzzed_data.ConsumeData(&env, sizeof(env));
  fuzzed_data.ConsumeData(&ctx, sizeof(ctx));

  // Call the function to be fuzzed
  decode_micromips_opc(&env, &ctx);

  return 0;
}