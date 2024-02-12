#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "log.h"

extern "C" {
#include <algorithm>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* format = stream.ConsumeRemainingBytesAsString().c_str();
  struct __va_list_tag args;
  va_start(args, format);
  log_commit_journal(nullptr, const_cast<char*>(format), &args);
  va_end(args);
  return 0;
}