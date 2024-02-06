#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libyang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the libyang context
  struct ly_ctx *ctx = ly_ctx_new(NULL, 0);
  if (!ctx) {
    return 0;
  }

  // Initialize the parsing context
  struct lysp_ctx *pctx = (struct lysp_ctx *)calloc(1, sizeof *pctx);
  if (!pctx) {
    ly_ctx_destroy(ctx, NULL);
    return 0;
  }

  // Initialize the extension instance
  struct lysp_ext_instance *ext = (struct lysp_ext_instance *)calloc(1, sizeof *ext);
  if (!ext) {
    free(pctx);
    ly_ctx_destroy(ctx, NULL);
    return 0;
  }

  // Call the target function
  int result = structure_parse(pctx, ext);

  // Cleanup
  free(ext);
  free(pctx);
  ly_ctx_destroy(ctx, NULL);

  return 0;
}