#include <stdint.h>
#include <json-c/json.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  json_object *obj = json_object_from_fd(0);

  if (json_object_is_type(obj, json_type_object)) {
    json_object_object_foreach(obj, key, val) {
      (void)json_object_get_type(val);
      (void)json_object_get_string(val);
    }
  }
  (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);

  json_object_put(obj);
  return 0;
}