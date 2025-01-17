#include <fuzzer/FuzzedDataProvider.h>
#include <gpac/dash.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize DASH context and group
  struct GF_DASHDmxCtx *ctx = (struct GF_DASHDmxCtx*) gf_malloc(sizeof(struct GF_DASHDmxCtx));
  struct GF_DASHGroup *group = (struct GF_DASHGroup*) gf_malloc(sizeof(struct GF_DASHGroup));

  // Consume data for DASH context and group
  stream.ConsumeData(ctx, sizeof(struct GF_DASHDmxCtx));
  stream.ConsumeData(group, sizeof(struct GF_DASHGroup));

  // Call the function to fuzz
  dashdmx_switch_segment(ctx, group);

  // Free allocated memory
  gf_free(ctx);
  gf_free(group);

  return 0;
}