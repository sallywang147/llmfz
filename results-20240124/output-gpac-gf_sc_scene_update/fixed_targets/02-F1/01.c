#include <stdio.h>
#include <unistd.h>

#include <gpac/constants.h>
#include <gpac/filters.h>
#include <gpac/scene.h>

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
  GF_Filter *insp = gf_fs_load_filter(fs, "inspect:deep:analyze=bs", &e);
  gf_fs_run(fs);
  gf_fs_del(fs);

  struct __tag_compositor *compositor = gf_sc_new_compositor(NULL);
  int ret = gf_sc_scene_update(compositor, NULL, NULL);
  gf_sc_del_compositor(compositor);

  unlink(filename);
  return ret;
}