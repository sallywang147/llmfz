#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libyang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the context
  struct lysp_ctx *ctx = (struct lysp_ctx *)calloc(1, sizeof(struct lysp_ctx));
  if (ctx == nullptr) {
    return 0;
  }

  // Initialize the statement
  struct lysp_stmt *stmt = (struct lysp_stmt *)calloc(1, sizeof(struct lysp_stmt));
  if (stmt == nullptr) {
    free(ctx);
    return 0;
  }

  // Initialize the parent node
  struct lysp_node *parent = (struct lysp_node *)calloc(1, sizeof(struct lysp_node));
  if (parent == nullptr) {
    free(ctx);
    free(stmt);
    return 0;
  }

  // Initialize the siblings node
  struct lysp_node *siblings = (struct lysp_node *)calloc(1, sizeof(struct lysp_node));
  if (siblings == nullptr) {
    free(ctx);
    free(stmt);
    free(parent);
    return 0;
  }

  // Call the target function
  int ret = lysp_stmt_list(ctx, stmt, parent, &siblings);

  // Clean up
  free(ctx);
  free(stmt);
  free(parent);
  free(siblings);

  return 0;
}