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
  if (size < sizeof(struct CPUMIPSState) + sizeof(struct DisasContext)) {
    return 0;
  }
  
  FuzzedDataProvider provider(data, size);
  
  struct CPUMIPSState env;
  struct DisasContext ctx;
  
  // Consume data for env and ctx from the provider
  provider.ConsumeData(&env, sizeof(struct CPUMIPSState));
  provider.ConsumeData(&ctx, sizeof(struct DisasContext));
  
  // Call the function to fuzz
  decode_nanomips_opc(&env, &ctx);

  return 0;
}