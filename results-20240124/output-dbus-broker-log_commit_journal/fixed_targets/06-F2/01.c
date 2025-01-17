#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "log.h"

extern "C" {
#include "fuzz-message.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  const std::string format = std::string(reinterpret_cast<const char*>(data), size);
  va_list args;
  va_start(args, format.c_str());
  log_commit_journal(nullptr, const_cast<char*>(format.c_str()), &args);
  va_end(args);
  return 0;
}