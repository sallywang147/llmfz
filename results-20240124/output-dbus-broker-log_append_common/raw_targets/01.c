 #include <stddef.h>
#include <stdint.h>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct Log log;
  log_init(&log);
  int level = stream.ConsumeIntegral<int>();
  int error = stream.ConsumeIntegral<int>();
  char *id = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *file = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  int line = stream.ConsumeIntegral<int>();
  char *func = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  log_append_common(&log, level, error, id, file, line, func);
  log_free(&log);
  return 0;
}