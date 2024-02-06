#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  
  std::string str1 = fuzzed_data.ConsumeRandomLengthString();
  std::string str2 = fuzzed_data.ConsumeRemainingBytesAsString();
  
  debug_log_callback(const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()));

  return 0;
}