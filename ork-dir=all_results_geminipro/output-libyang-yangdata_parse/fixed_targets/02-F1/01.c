#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "libyang.h"

extern "C" {
#include "yangdata.h"
}

int LLVMFuzzerTestOneInput(uint8_t const *buf, size_t len) {
  struct lysp_ctx *pctx = NULL;
  struct lysp_ext_instance *ext = NULL;
  static bool log = false;

  if (!log) {
    ly_log_options(0);
    log = true;
  }

  ext = lysp_ext_instance_new();
  if (ext == NULL) {
    fprintf(stderr, "Failed to create ext instance\n");
    exit(EXIT_FAILURE);
  }

  pctx = lysp_parse_mem(NULL, buf, len);
  if (pctx == NULL) {
    fprintf(stderr, "Failed to parse data\n");
    exit(EXIT_FAILURE);
  }

  yangdata_parse(pctx, ext);

  lysp_ext_instance_free(ext);
  lysp_ctx_destroy(pctx);

  return 0;
}