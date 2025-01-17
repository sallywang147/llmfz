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
  struct Log log;
  int r;

  if (size < sizeof(struct Log))
    return 0;

  memcpy(&log, data, sizeof(struct Log));

  if (log.data_len > size)
    return 0;

  log.data = (char *)data + sizeof(struct Log);

  r = log_commit_stderr(&log, NULL, NULL);
  if (r)
    return 0;

  return 0;
}