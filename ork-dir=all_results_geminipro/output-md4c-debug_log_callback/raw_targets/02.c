#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string log_message = stream.ConsumeRemainingBytesAsString();
  const std::string log_file = stream.ConsumeRemainingBytesAsString();
  debug_log_callback(const_cast<char*>(log_message.c_str()),
                     const_cast<char*>(log_file.c_str()));
  return 0;
}