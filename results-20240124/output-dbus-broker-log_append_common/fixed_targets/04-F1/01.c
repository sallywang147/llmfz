#include <stddef.h>
#include <stdint.h>

#include "log.h"

extern "C" {
void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log = {0};
  char *id = (char *)data;
  char *file = (char *)data + strlen(id) + 1;
  char *func = (char *)data + strlen(id) + strlen(file) + 2;
  log_append_common(&log, 0, 0, id, file, 0, func);
}
}