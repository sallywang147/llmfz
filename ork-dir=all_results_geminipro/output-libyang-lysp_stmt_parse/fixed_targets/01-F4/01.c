#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "lysp.h"

extern "C" {
#include "lysp_fuzz.h"
}

static int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct lysp_ctx *pctx;
  struct lysp_stmt *stmt;
  char *result;
  struct lysp_ext_instance *exts;

  pctx = lysp_ctx_new();
  if (!pctx) {
    return 0;
  }

  stmt = lysp_stmt_new();
  if (!stmt) {
    lysp_ctx_free(pctx);
    return 0;
  }

  result = malloc(size + 1);
  if (!result) {
    lysp_stmt_free(stmt);
    lysp_ctx_free(pctx);
    return 0;
  }

  memcpy(result, data, size);
  result[size] = '\0';

  // Call the target function
  lysp_stmt_parse(pctx, stmt, &result, &exts);

  free(result);
  lysp_stmt_free(stmt);
  lysp_ctx_free(pctx);

  return 0;
}