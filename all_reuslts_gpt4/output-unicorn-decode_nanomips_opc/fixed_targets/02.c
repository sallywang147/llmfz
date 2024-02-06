#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "cpu.h"
#include "disas/dis-asm.h"
#include "disas/bfd.h"
#include "exec/exec-all.h"
#include "tcg/tcg.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the required structures
  struct CPUMIPSState env;
  struct DisasContext ctx;

  // Fill the structures with fuzzed data
  stream.ConsumeData(&env, sizeof(env));
  stream.ConsumeData(&ctx, sizeof(ctx));

  // Call the target function
  decode_nanomips_opc(&env, &ctx);

  return 0;
}