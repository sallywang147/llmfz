#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "qemu/osdep.h"
#include "qemu/host-utils.h"
#include "qemu/disas.h"
#include "cpu.h"

extern "C" {
#include "qemu/mips.h"
#include "qemu/qemu-common.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }

  struct CPUMIPSState *env = (struct CPUMIPSState *)malloc(sizeof(*env));
  struct DisasContext *ctx = (struct DisasContext *)malloc(sizeof(*ctx));

  memset(env, 0, sizeof(*env));
  memset(ctx, 0, sizeof(*ctx));

  ctx->isa = MIPS_CPU_32;
  ctx->endianness = MIPS_CPU_LE;
  ctx->pc = 0;
  ctx->ins_len = 4;

  int ret = decode_nanomips_opc(env, ctx, data); // Added 'data' argument

  free(env);
  free(ctx);

  return ret;
}