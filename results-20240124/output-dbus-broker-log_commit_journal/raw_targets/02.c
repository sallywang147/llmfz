 #include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>

#include "log.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  log_init(&log);
  log_commit_journal(&log, (char *)data, (struct __va_list_tag *)data);
  return 0;
}