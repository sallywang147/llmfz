#include <stdint.h>

#include <json.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  char *null_terminated_input = (char *)malloc(size + 1);
  if (null_terminated_input == nullptr) {
    return 0;
  }
  memcpy(null_terminated_input, data, size);
  null_terminated_input[size] = '\0';

  json_object *obj = json_tokener_parse(null_terminated_input);
  if (obj != nullptr) {
    (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);
    json_object_put(obj);
  }

  free(null_terminated_input);
  return 0;
}