#include "flb_fuzz_header.h"
#include <fluent-bit/flb_lib_ctx.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" {
#include <fluent-bit/flb_malloc.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  /* Set fuzzer-malloc chance of failure */
  flb_malloc_p = 0;
  flb_malloc_mod = 25000;

  /* Limit the size of the config files to 32KB. */
  if (size > 32768) {
    return 0;
  }

  /* Write the config file to a location we know OSS-Fuzz has */
  char filename[256];
  sprintf(filename, "/tmp/libfuzzer.%d", getpid());
  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }
  fwrite(conf_file, strlen(conf_file), 1, fp);
  fclose(fp);

  /* Now parse random data based on the config files */
  struct flb_lib_ctx *ctx = NULL;
  ctx = flb_lib_ctx_init();
  int ret = flb_lib_ctx_conf_file(filename, ctx);
  if (ret == 0) {
    flb_start_trace(ctx);
  }
  flb_lib_ctx_exit(ctx);

  /* clean up the file */
  unlink(filename);

  return 0;
}