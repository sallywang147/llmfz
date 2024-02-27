#include <stdio.h>
#include <unistd.h>

#include <gpac/constants.h>
#include <gpac/dash.h>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
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

  GF_DashClient *dash = gf_dash_new_client();
  GF_FilterSession *fs = gf_fs_new_defaults(0);
  GF_Filter *src = gf_fs_load_source(fs, filename, NULL, NULL, &e);
  GF_Filter *dash_src = gf_fs_load_filter(fs, "dash:manifest", &e);
  gf_fs_run(fs);
  gf_dash_update_manifest(dash);
  gf_fs_del(fs);

  unlink(filename);
  return 0;
}