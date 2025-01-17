#include <stdint.h>

#include <json.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  json_object *obj = json_object_from_fd_ex(0, 0);
  if (obj == NULL) {
    return 0;
  }
  json_object_put(obj);
  return 0;
}