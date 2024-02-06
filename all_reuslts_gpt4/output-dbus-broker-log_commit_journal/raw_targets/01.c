#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Log log;
  log_init(&log);

  std::string format = stream.ConsumeRandomLengthString();
  __va_list_tag args;

  log_commit_journal(&log, format.c_str(), &args);

  log_destroy(&log);

  return 0;
}