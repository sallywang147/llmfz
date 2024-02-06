#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "log.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log *log = log_new();
  if (log == NULL) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);

  size_t format_len = stream.ConsumeIntegralInRange<size_t>(0, size);
  char *format = stream.ConsumeBytes<char>(format_len);
  __va_list_tag args;
  va_start(args, format);
  int ret = log_commit_journal(log, format, &args);
  va_end(args);
  log_free(log);
  free(format);
  return ret;
}