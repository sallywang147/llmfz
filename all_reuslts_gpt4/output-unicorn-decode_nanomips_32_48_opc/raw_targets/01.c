#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "disas/disas.h"
#include "target/mips/cpu.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(struct CPUMIPSState) + sizeof(struct DisasContext)) {
    return 0;
  }
  
  FuzzedDataProvider fuzzed_data(data, size);

  struct CPUMIPSState env;
  fuzzed_data.ConsumeData(&env, sizeof(struct CPUMIPSState));

  struct DisasContext ctx;
  fuzzed_data.ConsumeData(&ctx, sizeof(struct DisasContext));

  decode_nanomips_32_48_opc(&env, &ctx);

  return 0;
}