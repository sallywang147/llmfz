#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#include "log.h"

extern "C" {
#include <stdio.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  memset(&log, 0, sizeof(log));
  log.level = LOG_INFO;
  char *format = (char *)data;
  size_t format_len = size;
  if (format_len > 0 && format[format_len - 1] == '\n')
    format_len--;
  format[format_len] = '\0';
  log_vcommitf(&log, format, (struct __va_list_tag *)data + format_len + 1);
  return 0;
}