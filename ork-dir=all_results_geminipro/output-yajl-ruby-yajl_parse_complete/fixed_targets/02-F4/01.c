#include <yajl/yajl_parse.h>
#include <yajl/yajl_gen.h>
#include <yajl/yajl_tree.h>

extern "C" {
#include <stddef.h>
#include <stdint.h>
}

static yajl_val parse_json(const uint8_t *data, size_t len) {
  yajl_val val = NULL;
  yajl_handle hand = yajl_alloc(NULL, NULL);
  if (!hand) {
    return NULL;
  }
  yajl_status status = yajl_parse(hand, data, len);
  if (status != yajl_status_ok) {
    yajl_free(hand);
    return NULL;
  }
  status = yajl_parse_complete(hand);
  if (status != yajl_status_ok) {
    yajl_free(hand);
    return NULL;
  }
  val = yajl_get_parse_result(hand);
  yajl_free(hand);
  return val;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t len) {
  yajl_val val = parse_json(data, len);
  if (!val) {
    return 0;
  }
  yajl_tree_free(val);
  return 0;
}