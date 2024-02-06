#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct lysp_ext_instance *ext = NULL;
  struct lysp_ctx *pctx = NULL;
  LY_ERR err;

  err = lysp_parse_mem(NULL, data, size, LYS_IN_YANG, NULL, &pctx);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to parse data\n");
    exit(EXIT_FAILURE);
  }

  err = lysp_ext_instance_new(pctx, &ext);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to create ext instance\n");
    exit(EXIT_FAILURE);
  }

  err = structure_parse(pctx, ext);
  if (err != LY_SUCCESS) {
    fprintf(stderr, "Failed to parse structure\n");
    exit(EXIT_FAILURE);
  }

  lysp_ext_instance_free(ext);
  lysp_ctx_destroy(pctx);

  return 0;
}