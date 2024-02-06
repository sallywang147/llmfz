#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>

#include "log.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct Log *log = log_new();
  if (log == NULL) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string format = stream.ConsumeRandomLengthString();
  if (format.empty()) {
    log_free(log);
    return 0;
  }

  struct __va_list_tag args;
  memset(&args, 0, sizeof(args));

  int result = log_commit_journal(log, const_cast<char*>(format.c_str()), &args);

  log_free(log);
  return result;
}