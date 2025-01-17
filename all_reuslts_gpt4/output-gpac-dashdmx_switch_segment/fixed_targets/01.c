#include <fuzzer/FuzzedDataProvider.h>
#include <gpac/dash.h>
#include <gpac/internal/dash.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize DASH context and group
  GF_DASHDmxCtx ctx;
  GF_DASHGroup group;

  // Consume data to fill the structures
  ctx.dash = (GF_DASHFileIO *)stream.ConsumeBytes<uint8_t>(sizeof(GF_DASHFileIO)).data();
  ctx.nb_groups = stream.ConsumeIntegral<int>();
  ctx.groups = (GF_DASHGroup **)stream.ConsumeBytes<uint8_t>(sizeof(GF_DASHGroup *) * ctx.nb_groups).data();
  ctx.in_period_setup = stream.ConsumeBool();
  ctx.in_period_resetting = stream.ConsumeBool();
  ctx.in_group_setup = stream.ConsumeBool();
  ctx.in_group_resetting = stream.ConsumeBool();

  group.dash = ctx.dash;
  group.active_rep_index = stream.ConsumeIntegral<int>();
  group.max_cached_duration = stream.ConsumeIntegral<u32>();
  group.is_downloading = stream.ConsumeBool();
  group.is_buffering = stream.ConsumeBool();
  group.buffer_min_ms = stream.ConsumeIntegral<u32>();
  group.buffer_max_ms = stream.ConsumeIntegral<u32>();

  // Call the target function
  dashdmx_switch_segment(&ctx, &group);

  return 0;
}