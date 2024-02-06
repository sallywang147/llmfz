#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "libyang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lysp_ctx pctx;
  struct lysp_stmt stmt;
  char* result;
  struct lysp_ext_instance* exts;

  // Initialize the context
  pctx.ctx = ly_ctx_new(NULL, 0);
  pctx.main_ctx = &pctx;
  pctx.parsed_mod = NULL;
  pctx.parsing = NULL;
  pctx.line = 0;
  pctx.indent = 0;
  pctx.type = LY_STMT_NONE;
  pctx.flags = 0;
  pctx.keyword = NULL;

  // Initialize the statement
  stmt.parent = NULL;
  stmt.name = NULL;
  stmt.flags = 0;
  stmt.arg.str = NULL;
  stmt.child = NULL;
  stmt.next = NULL;

  // Initialize the result
  result = NULL;

  // Initialize the extensions
  exts = NULL;

  // Call the function to fuzz
  lysp_stmt_parse(&pctx, &stmt, &result, &exts);

  // Cleanup
  ly_ctx_destroy(pctx.ctx, NULL);

  return 0;
}