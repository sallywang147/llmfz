#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "proj.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize the context
  struct pj_ctx *ctx = proj_context_create();

  // Initialize the object list
  struct PJ_OBJ_LIST *obj_list = (struct PJ_OBJ_LIST *)malloc(sizeof(struct PJ_OBJ_LIST));

  // Consume data for the integer parameter
  int int_arg = stream.ConsumeIntegral<int>();

  // Initialize the coordinate
  union PJ_COORD *coord = (union PJ_COORD *)malloc(sizeof(union PJ_COORD));

  // Call the function to be fuzzed
  proj_get_suggested_operation(ctx, obj_list, int_arg, coord);

  // Cleanup
  proj_context_destroy(ctx);
  free(obj_list);
  free(coord);

  return 0;
}