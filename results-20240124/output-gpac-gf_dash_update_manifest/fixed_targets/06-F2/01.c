#include <stdio.h>
#include <unistd.h>

#include <gpac/constants.h>
#include <gpac/filters.h>

extern "C" {
#include <gpac/dash.h>
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

  GF_FilterSession *fs = gf_fs_new_defaults(GF_FILTER_SESSION_FLAGS_NONE);
  GF_Filter *src = gf_fs_load_source(fs, filename, NULL, NULL, &e);
  GF_Filter *dash = gf_fs_load_filter(fs, "dash:stream=0", &e);
  gf_fs_run(fs);
  gf_dash_update_manifest(dash);
  gf_fs_del(fs);

  unlink(filename);
  return 0;
}