#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "log.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  log_init(&log, NULL);
  log_commit_stderr(&log, (char *)data, (struct __va_list_tag *)data);
  return 0;
}