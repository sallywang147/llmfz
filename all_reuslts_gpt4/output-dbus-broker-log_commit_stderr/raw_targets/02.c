#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

#include "log.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a log object
  struct Log *log = log_create();
  if (log == NULL) {
    return 0;
  }

  // Prepare a format string
  std::string format = stream.ConsumeRandomLengthString().c_str();

  // Prepare the argument list
  va_list args;
  va_start(args, format.c_str());

  // Call the function under test
  log_commit_stderr(log, const_cast<char *>(format.c_str()), args);

  va_end(args);
  log_free(log);

  return 0;
}