#include <stddef.h>
#include <stdint.h>

#include "log.h"

extern "C" {
#include <libunwind.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  _c_cleanup_(log_unrefp) Log *log = NULL;
  int r;

  if (size < sizeof(struct LogHeader))
    return 0;

  r = log_new(&log, (struct LogHeader *)data);
  if (r != 0)
    return 0;

  if (log->n_data > size)
    return 0;

  memcpy(log->data + sizeof(struct LogHeader), data + sizeof(struct LogHeader),
         log->n_data - sizeof(struct LogHeader));

  r = log_commit_journal(log, "%s", data);
  if (r)
    return 0;

  return 0;
}