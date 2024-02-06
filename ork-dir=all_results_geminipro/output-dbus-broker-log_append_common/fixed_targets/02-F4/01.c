#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "log.h"

extern "C" {
#include "llvm/Support/raw_ostream.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 8) {
    return 0;
  }
  uint8_t *p = (uint8_t *)data;
  log_append_common((struct Log *)p, p[4], p[5], (char *)p + 6, (char *)p + 8, p[12], (char *)p + 13);
  return 0;
}

struct Log {
  uint8_t type;
  uint8_t subtype;
  char *data;
  uint32_t data_len;
  uint8_t pid;
  char *pid_str;
};

void log_append_common(struct Log *log, uint8_t type, uint8_t subtype, char *data, char *pid_str, uint8_t pid) {
  log->type = type;
  log->subtype = subtype;
  log->data = data;
  log->data_len = strlen(data);
  log->pid = pid;
  log->pid_str = pid_str;
}