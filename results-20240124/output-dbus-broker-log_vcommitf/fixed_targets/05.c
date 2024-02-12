#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  char *format = (char *)data;
  struct __va_list_tag args;
  va_start(args, format);
  log_vcommitf(&log, format, &args);
  va_end(args);
  return 0;
}