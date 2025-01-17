#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "proj.h"

extern "C" {
#include "pj_ctx.h"
#include "pj_operation_list.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* input_cstr = new char[input.size() + 1];
  std::strcpy(input_cstr, input.c_str());

  struct pj_ctx* context = pj_ctx_alloc();
  if (context == nullptr) {
    return 0;
  }
  PJ_OPERATION_LIST* operation_list = PJ_OPERATION_LIST_create(context);
  if (operation_list == nullptr) {
    pj_ctx_free(context);
    return 0;
  }
  std::vector* operations = operation_list->getPreparedOperations(operation_list, context);
  if (operations == nullptr) {
    PJ_OPERATION_LIST_free(operation_list);
    pj_ctx_free(context);
    return 0;
  }
  delete[] input_cstr;
  PJ_OPERATION_LIST_free(operation_list);
  pj_ctx_free(context);
  return 0;
}