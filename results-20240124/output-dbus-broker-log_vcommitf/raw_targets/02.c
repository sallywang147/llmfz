 #include <fuzzer/FuzzedDataProvider.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct Log log;
  memset(&log, 0, sizeof(log));
  log.level = LOG_INFO;
  log.log_file = stream.ConsumeRandomLengthString().c_str();
  log.log_level = stream.ConsumeIntegral<int>();
  log.log_size = stream.ConsumeIntegral<int>();
  log.log_type = stream.ConsumeIntegral<int>();
  log.log_time = stream.ConsumeIntegral<int>();
  log.log_thread = stream.ConsumeIntegral<int>();
  log.log_func = stream.ConsumeRandomLengthString().c_str();
  log.log_line = stream.ConsumeIntegral<int>();
  log.log_msg = stream.ConsumeRandomLengthString().c_str();
  log.log_data = stream.ConsumeRemainingBytes().data();
  log.log_data_len = stream.ConsumeIntegral<int>();
  log_vcommitf(&log, "%s", stream.ConsumeRandomLengthString().c_str());
  return 0;
}