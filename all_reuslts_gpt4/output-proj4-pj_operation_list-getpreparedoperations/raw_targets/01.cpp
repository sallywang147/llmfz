#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "proj.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize a PJ_OPERATION_LIST object
  struct PJ_OPERATION_LIST op_list;

  // Initialize a pj_ctx object
  struct pj_ctx ctx;

  // Call the function with the fuzzed inputs
  std::vector *prepared_ops = PJ_OPERATION_LIST::getPreparedOperations(&op_list, &ctx);

  // Cleanup
  delete prepared_ops;

  return 0;
}