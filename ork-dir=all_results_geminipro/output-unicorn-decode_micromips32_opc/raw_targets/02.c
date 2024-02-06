#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "qemu/cpu-all.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    qemu_init_cpu();
    initialized = true;
  }

  struct CPUMIPSState *env = qemu_new_cpu(NULL);
  struct DisasContext *ctx = qemu_new_disas_context();

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    uint32_t instr = provider.ConsumeIntegral<uint32_t>();
    decode_micromips32_opc(env, ctx, instr);
  }

  qemu_free_cpu(env);
  qemu_free_disas_context(ctx);

  return 0;
}