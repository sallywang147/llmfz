#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log = {0};
  log.level = LOG_CRIT;
  log_vcommitf(&log, (char *)data, (struct __va_list_tag *)data);
  return 0;
}