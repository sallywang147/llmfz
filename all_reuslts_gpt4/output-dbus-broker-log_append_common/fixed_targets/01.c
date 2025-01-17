#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a log structure
  struct Log log;

  // Consume data to generate inputs for the function
  int level = provider.ConsumeIntegral<int>();
  int error = provider.ConsumeIntegral<int>();
  int line = provider.ConsumeIntegral<int>();
  std::string id = provider.ConsumeRandomLengthString();
  std::string file = provider.ConsumeRandomLengthString();
  std::string func = provider.ConsumeRandomLengthString();

  // Call the function with the fuzzed inputs
  log_append_common(&log, level, error, const_cast<char*>(id.c_str()), const_cast<char*>(file.c_str()), line, const_cast<char*>(func.c_str()));

  return 0;
}