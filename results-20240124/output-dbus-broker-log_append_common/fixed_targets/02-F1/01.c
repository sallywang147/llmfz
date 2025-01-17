#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include "log.h"
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct Log log;
  log_init(&log, NULL, NULL);
  FuzzedDataProvider stream(data, size);
  int level = stream.ConsumeIntegral<int>();
  int error = stream.ConsumeIntegral<int>();
  char *id = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *file = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  int line = stream.ConsumeIntegral<int>();
  char *func = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  log_append_common(&log, level, error, id, file, line, func);
}