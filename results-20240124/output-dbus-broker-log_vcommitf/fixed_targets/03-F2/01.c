#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include <va_list.h>
#include "log.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  log.flags = 0;
  log.fd = -1;

  FuzzedDataProvider stream(data, size);
  const char *format = stream.ConsumeRemainingBytesAsString().c_str();
  va_list args;
  va_start(args, format);
  log_vcommitf(&log, (char *)format, &args);
  va_end(args);
  return 0;
}