#include "flb_fuzz_header.h"
#include <fluent-bit/flb_lib.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
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
  struct flb_config *config = NULL;
  config = flb_config_init();
  int ret = flb_parser_conf_file(filename, config);
  if (ret == 0) {
    struct mk_list *head = NULL;
    mk_list_foreach(head, &config->parsers) {
      size_t out_size;
      char *out_buf = NULL;
      struct flb_parser *parser = NULL;
      struct flb_time out_time;
      parser = mk_list_entry(head, struct flb_parser, _head);
      flb_parser_do(parser, (const char *)data, size, (void **)&out_buf, &out_size, &out_time);
      if (out_buf != NULL) {
        free(out_buf);
      }
    }
  }
  flb_parser_exit(config);
  flb_config_exit(config);

  /* clean up the file */
  unlink(filename);

  /* Now let's call flb_start_trace */
  struct flb_lib_ctx *ctx = flb_lib_ctx_create();
  if (!ctx) {
    return 0;
  }
  flb_start_trace(ctx);
  flb_lib_ctx_destroy(ctx);

  return 0;
}