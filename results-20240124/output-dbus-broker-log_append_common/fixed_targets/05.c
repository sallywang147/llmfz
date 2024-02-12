#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "log.h"

extern "C" {
#include "log.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Log *log = log_new();
  int level = stream.ConsumeIntegralInRange<int>(0, 10);
  int error = stream.ConsumeIntegralInRange<int>(0, 10);
  char *id = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size)).c_str();
  char *file = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size)).c_str();
  int line = stream.ConsumeIntegralInRange<int>(0, 10);
  char *func = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size)).c_str();

  log_append_common(log, level, error, id, file, line, func);

  log_destroy(log);

  return 0;
}