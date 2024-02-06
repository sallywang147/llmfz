#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"

extern "C" {
#include <cstdarg>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  _c_cleanup_(log_freep) struct Log *log = log_new();
  if (log == NULL)
    return 0;

  log->fd = -1;

  char *format = (char *)data;
  if (size < 1)
    return 0;

  size_t fmt_len = 0;
  while (fmt_len < size && format[fmt_len] != '\0')
    fmt_len++;

  if (fmt_len == size)
    return 0;

  va_list args;
  va_start(args, format);

  log_commit_stderr(log, format, args);

  va_end(args);

  return 0;
}