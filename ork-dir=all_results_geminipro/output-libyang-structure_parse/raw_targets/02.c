#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput(uint8_t const *buf, size_t len) {
  struct lysp_ctx *pctx = NULL;
  struct lysp_ext_instance *ext = NULL;
  static bool log = false;

  if (!log) {
    ly_log_options(0);
    log = true;
  }

  pctx = lysp_ctx_new(NULL);
  if (!pctx) {
    fprintf(stderr, "Failed to create context\n");
    exit(EXIT_FAILURE);
  }

  ext = malloc(sizeof(*ext));
  if (!ext) {
    fprintf(stderr, "Failed to allocate memory for extension instance\n");
    exit(EXIT_FAILURE);
  }

  char *data = malloc(len + 1);
  if (data == NULL) {
    return 0;
  }
  memcpy(data, buf, len);
  data[len] = 0;

  int ret = structure_parse(pctx, ext, data);

  lysp_ctx_destroy(pctx);
  free(ext);
  free(data);

  return ret;
}