#include <stdio.h>
#include <unistd.h>

#include <gpac/constants.h>
#include <gpac/dash.h>

extern "C" {
#include <gpac/fileio.h>
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

  GF_DashFileIO *dash_io = gf_fileio_open(filename);
  GF_DashClient *dash = gf_dash_new(dash_io, NULL);
  gf_dash_set_info(dash, filename, NULL);
  gf_dash_update_manifest(dash);
  gf_dash_delete(dash);

  unlink(filename);
  return 0;
}