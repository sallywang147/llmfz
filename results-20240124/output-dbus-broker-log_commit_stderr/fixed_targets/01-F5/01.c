#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "log.h"

extern "C" {
#include "log.h"
}

struct Log {
  int (*commit_stderr)(struct Log *log, char *format, struct __va_list_tag *args);
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string format = stream.ConsumeRemainingBytesAsString();
  const char* fmt = format.c_str();
  Log log;
  log.commit_stderr = &log_commit_stderr;
  log_commit_stderr(&log, (char*)fmt, nullptr);
  return 0;
}