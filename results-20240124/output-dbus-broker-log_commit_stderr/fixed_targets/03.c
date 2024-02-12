#include <stddef.h>
#include <stdint.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  log_init(&log, 0, 0);

  log_commit_stderr(&log, (char *)data, NULL);

  return 0;
}