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
  lysp_stmt_parse(pctx, stmt, result);

  free(result);
  lysp_stmt_free(stmt);
  lysp_ctx_free(pctx);

  return 0;
}
```

The issue was that the `lysp_stmt_parse` function takes three arguments, but the code was passing four. The fourth argument, `&exts`, is not needed for this function.

The corrected code removes the `&exts` argument from the call to `lysp_stmt_parse`.