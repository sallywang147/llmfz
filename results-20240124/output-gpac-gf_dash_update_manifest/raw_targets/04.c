 #include <stdio.h>
#include <unistd.h>

#include <gpac/constants.h>
#include <gpac/dash.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char filename[256];
  GF_Err e;
  sprintf(filename, "/tmp/libfuzzer.%d", getpid());

  FILE *fp = fopen(filename, "wb");
  if (!fp)
    return 0;
  fwrite(data, size, 1, fp);
  fclose(fp);

  GF_DashClient *dash = gf_dash_new();
  gf_dash_set_uri(dash, filename, NULL);
  gf_dash_update_manifest(dash);
  gf_dash_delete(dash);

  unlink(filename);
  return 0;
}