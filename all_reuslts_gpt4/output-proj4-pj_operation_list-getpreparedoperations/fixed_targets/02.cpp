#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "proj.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a PJ_OPERATION_LIST object
  struct PJ_OPERATION_LIST operation_list;

  // Create a pj_ctx object
  struct pj_ctx context;

  // Initialize the PJ_OPERATION_LIST and pj_ctx objects with random data
  size_t consumed = stream.ConsumeData(&operation_list, sizeof(operation_list));
  if(consumed != sizeof(operation_list)) return 0;

  consumed = stream.ConsumeData(&context, sizeof(context));
  if(consumed != sizeof(context)) return 0;

  // Call the target function
  std::vector * result = PJ_OPERATION_LIST::getPreparedOperations(&operation_list, &context);

  // Free the result
  delete result;

  return 0;
}