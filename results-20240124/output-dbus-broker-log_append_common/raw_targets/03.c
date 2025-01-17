 #include <stddef.h>
#include <stdint.h>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log *log = log_new(1024, 1024);
  log_append_common(log, 0, 0, (char *)data, (char *)data, 0, (char *)data);
  log_free(log);
  return 0;
}