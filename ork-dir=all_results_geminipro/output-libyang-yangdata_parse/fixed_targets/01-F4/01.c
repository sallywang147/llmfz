#include <stdio.h>
#include <stdlib.h>

#include "libyang.h"
#include "yangdata.h"

int LLVMFuzzerTestOneInput(uint8_t const *buf, size_t len) {
  struct lysp_ext_instance *ext = NULL;
  struct lysp_ctx *pctx = NULL;
  LY_ERR err;

  err = lysp_parse_mem(NULL, buf, len, LYS_IN_YANG, &pctx);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to parse schema\n");
    exit(EXIT_FAILURE);
  }

  err = lysp_ext_instance_new(&ext);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to create extension instance\n");
    exit(EXIT_FAILURE);
  }

  err = yangdata_parse(pctx, ext);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to parse data\n");
    exit(EXIT_FAILURE);
  }

  lysp_ext_instance_free(ext);
  lysp_ctx_free(pctx);

  return 0;
}