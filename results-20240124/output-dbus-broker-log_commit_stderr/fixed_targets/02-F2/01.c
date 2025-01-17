#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log = {
    .fd = -1,
    .level = LOG_DEBUG,
    .prefix = NULL,
    .flags = 0,
    .priv = NULL,
  };

  char *format = (char *)data;
  size_t format_len = size;

  struct __va_list_tag args;
  va_start(args, format);

  log_commit_stderr(&log, format, &args);

  va_end(args);

  return 0;
}