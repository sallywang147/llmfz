#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "libyang.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct lysp_ctx *pctx = NULL;
  struct lysp_stmt *stmt = NULL;
  char *result = NULL;
  struct lysp_ext_instance **exts = NULL;

  pctx = lysp_ctx_new(NULL);
  if (!pctx) {
    fprintf(stderr, "Failed to create context\n");
    exit(EXIT_FAILURE);
  }

  stmt = lysp_stmt_new(NULL, LYS_STMT_MODULE);
  if (!stmt) {
    fprintf(stderr, "Failed to create statement\n");
    exit(EXIT_FAILURE);
  }

  lysp_stmt_parse(pctx, stmt, &result, exts);

  free(result);
  lysp_stmt_free(stmt);
  lysp_ctx_destroy(pctx);

  return 0;
}