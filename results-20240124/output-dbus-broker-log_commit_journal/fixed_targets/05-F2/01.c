#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  int r;

  log_init(&log, 0, 0, NULL);

  r = log_commit_journal(&log, (char *)data, (struct __va_list_tag *)data);
  if (r)
    return 0;

  return 0;
}