#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "dashdmx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct GF_DASHDmxCtx* ctx = (struct GF_DASHDmxCtx*)malloc(sizeof(struct GF_DASHDmxCtx));
  if (ctx == nullptr) {
    return 0;
  }
  memset(ctx, 0, sizeof(struct GF_DASHDmxCtx));
  ctx->nb_groups = 1;
  ctx->groups = (struct GF_DASHGroup*)malloc(sizeof(struct GF_DASHGroup));
  memset(ctx->groups, 0, sizeof(struct GF_DASHGroup));

  struct GF_DASHGroup* group = ctx->groups;
  group->id = stream.ConsumeIntegral<uint32_t>();
  group->nb_reps = stream.ConsumeIntegral<uint32_t>();
  group->nb_segs = stream.ConsumeIntegral<uint32_t>();
  group->segs = (struct GF_DASHSegment*)malloc(sizeof(struct GF_DASHSegment) * group->nb_segs);
  memset(group->segs, 0, sizeof(struct GF_DASHSegment) * group->nb_segs);

  for (uint32_t i = 0; i < group->nb_segs; i++) {
    group->segs[i].index = stream.ConsumeIntegral<uint32_t>();
    group->segs[i].url = stream.ConsumeRemainingBytesAsString();
  }

  dashdmx_switch_segment(ctx, group);

  free(ctx->groups->segs);
  free(ctx->groups);
  free(ctx);
  return 0;
}