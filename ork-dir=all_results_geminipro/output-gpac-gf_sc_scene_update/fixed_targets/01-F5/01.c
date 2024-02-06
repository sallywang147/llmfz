#include <libavutil/avutil.h>
#include <stdio.h>
#include <unistd.h>

#include <gpac/constants.h>
#include <gpac/filters.h>

extern "C" {
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
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
  GF_Filter *insp = gf_fs_load_filter(fs, "inspect:deep:analyze=bs", &e);
  gf_fs_run(fs);
  gf_fs_del(fs);

  unlink(filename);

  GF_Compositor *compositor = gf_compositor_new();
  gf_sc_scene_update(compositor, "video", "0");
  gf_compositor_del(compositor);

  return 0;
}