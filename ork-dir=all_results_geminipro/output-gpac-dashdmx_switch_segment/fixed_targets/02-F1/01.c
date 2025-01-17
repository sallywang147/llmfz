#include <stdio.h>
#include <unistd.h>

extern "C" {
#include <gpac/constants.h>
#include <gpac/dashdmx.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char filename[256];
  GF_Err e;
  sprintf(filename, "/tmp/libfuzzer.%d", getpid());

  FILE *fp = fopen(filename, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  GF_FilterSession *fs = gf_fs_new_defaults(0);
  GF_Filter *src = gf_fs_load_source(fs, filename, NULL, NULL, &e);
  GF_Filter *dashdmx = gf_fs_load_filter(fs, "dashdmx:segment", &e);
  GF_DASHDmxCtx *ctx = gf_dashdmx_get_ctx(dashdmx);
  GF_DASHGroup *group = gf_dashdmx_get_group(dashdmx);
  gf_fs_run(fs);
  dashdmx_switch_segment(ctx, group);
  gf_fs_del(fs);

  unlink(filename);
  return 0;
}