#include <stddef.h>
#include <stdint.h>

#include "log.h"

extern "C" {
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  log_init(&log);
  log_commit_journal(&log, (char *)data, NULL);
  log_fini(&log);
  return 0;
}