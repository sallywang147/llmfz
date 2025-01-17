#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize log
  struct Log log;
  log_init(&log, LOG_DEBUG, NULL);

  // Get format string from fuzzer input
  std::string format = stream.ConsumeRandomLengthString();
  if (format.empty()) {
    return 0;
  }

  // Initialize va_list
  va_list args;
  va_start(args, format.c_str());

  // Call the target function
  log_commit_stderr(&log, const_cast<char*>(format.c_str()), args);

  va_end(args);

  return 0;
}