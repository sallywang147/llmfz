#include <stdint.h>

#include <json.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const char *data1 = reinterpret_cast<const char *>(data);
  int error;
  json_object *obj = json_tokener_parse_verbose(data1, &error);

  if (obj != nullptr) {
    if (json_object_is_type(obj, json_type_object)) {
      json_object_object_foreach(obj, key, val) {
        (void)json_object_get_type(val);
        (void)json_object_get_string(val);
      }
    }
    (void)json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY | JSON_C_TO_STRING_SPACED);

    json_object_put(obj);
  }

  return 0;
}