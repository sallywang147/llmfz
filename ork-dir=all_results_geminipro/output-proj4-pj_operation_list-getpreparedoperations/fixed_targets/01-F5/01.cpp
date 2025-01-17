#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

#include "libfuzzer/libfuzzer_macro.h"

extern "C" {
#include "pjsua2.h"
}

namespace {
class PJ_OPERATION_LIST {
 public:
  std::vector<pj_operation*>* getPreparedOperations(pj_operation_list* list,
                                                    pj_ctx* ctx);
};

std::vector<pj_operation*>* PJ_OPERATION_LIST::getPreparedOperations(
    pj_operation_list* list, pj_ctx* ctx) {
  std::vector<pj_operation*>* vec = new std::vector<pj_operation*>;
  for (size_t i = 0; i < list->count; ++i) {
    pj_operation* op = list->arr[i];
    if (op->op_id == PJ_OPERATION_ID_INVITE) {
      vec->push_back(op);
    }
  }
  return vec;
}
}  // namespace

DEFINE_PROTO_FUZZER(const uint8_t* data, size_t size) {
  pj_operation_list* list =
      reinterpret_cast<pj_operation_list*>(const_cast<uint8_t*>(data));
  pj_ctx* ctx = pj_create_null_ctx();
  PJ_OPERATION_LIST op_list;
  std::vector<pj_operation*>* vec = op_list.getPreparedOperations(list, ctx);
  pj_ctx_free(ctx);
  delete vec;
}