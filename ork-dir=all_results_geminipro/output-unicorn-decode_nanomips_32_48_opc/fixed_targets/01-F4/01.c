#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "cpu.h"
#include "disas.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 4) {
    return 0;
  }

  struct CPUMIPSState* env = (struct CPUMIPSState*)malloc(sizeof(struct CPUMIPSState));
  memset(env, 0, sizeof(struct CPUMIPSState));

  struct DisasContext* ctx = (struct DisasContext*)malloc(sizeof(struct DisasContext));
  memset(ctx, 0, sizeof(struct DisasContext));

  extern "C" void decode_nanomips_32_48_opc(struct CPUMIPSState* env, struct DisasContext* ctx, const uint8_t* data, size_t size);  // Pass the data and size to the function

  decode_nanomips_32_48_opc(env, ctx, data, size);  // Pass the data and size to the function

  free(env);
  free(ctx);

  return 0;
}