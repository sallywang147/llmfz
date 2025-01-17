#include <fuzzer/FuzzedDataProvider.h>
#include <cstdarg>
#include <cstdint>
#include <cstddef>
#include <cstring>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  // Create a log object
  Log *log = log_new();
  if (!log) {
    return 0;
  }

  // Consume data as a format string
  std::string format = fuzzed_data.ConsumeRemainingBytesAsString();

  // Create a va_list with no arguments
  va_list args;
  va_start(args, format.c_str());
  va_end(args);

  // Call the function to fuzz
  log_vcommitf(log, const_cast<char*>(format.c_str()), reinterpret_cast<struct __va_list_tag *>(args));

  // Clean up
  log_free(log);

  return 0;
}