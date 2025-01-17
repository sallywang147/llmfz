#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

#include "log.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int level = stream.ConsumeIntegral<int>();
  int error = stream.ConsumeIntegral<int>();
  int line = stream.ConsumeIntegral<int>();
  
  std::string id = stream.ConsumeRandomLengthString();
  std::string file = stream.ConsumeRandomLengthString();
  std::string func = stream.ConsumeRandomLengthString();

  struct Log log;
  
  log_append_common(&log, level, error, const_cast<char*>(id.c_str()), const_cast<char*>(file.c_str()), line, const_cast<char*>(func.c_str()));

  return 0;
}