#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct Log log;
  const int level = stream.ConsumeIntegral<int>();
  const int error = stream.ConsumeIntegral<int>();
  const std::string id = stream.ConsumeRemainingBytesAsString();
  const std::string file = stream.ConsumeRemainingBytesAsString();
  const int line = stream.ConsumeIntegral<int>();
  const std::string func = stream.ConsumeRemainingBytesAsString();
  log_append_common(&log, level, error, const_cast<char*>(id.c_str()),
                     const_cast<char*>(file.c_str()), line,
                     const_cast<char*>(func.c_str()));
  return 0;
}