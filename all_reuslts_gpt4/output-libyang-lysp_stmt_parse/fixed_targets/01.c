#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libyang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lysp_ctx pctx;
  struct lysp_stmt stmt;
  char *result;
  struct lysp_ext_instance *exts;

  // Initialize the context
  memset(&pctx, 0, sizeof(pctx));

  // Initialize the statement
  memset(&stmt, 0, sizeof(stmt));

  // Initialize the result
  result = NULL;

  // Initialize the extension instances
  exts = NULL;

  // Call the function to fuzz
  lysp_stmt_parse(&pctx, &stmt, &result, &exts);

  // Clean up
  if (result != NULL) {
    free(result);
  }

  if (exts != NULL) {
    free(exts);
  }

  return 0;
}