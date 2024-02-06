#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

extern "C" {
#include "json_object.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  json_object *obj = json_object_from_fd_ex(0, 1);
  if (obj) {
    json_object_put(obj);
  }
  return 0;
}