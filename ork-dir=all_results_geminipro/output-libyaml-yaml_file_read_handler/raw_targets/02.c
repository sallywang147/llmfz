#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string data_str = stream.ConsumeRemainingBytesAsString();
  const std::string buffer_str = stream.ConsumeRemainingBytesAsString();
  const size_t size_read = stream.ConsumeIntegral<size_t>();

  char* data_ptr = const_cast<char*>(data_str.c_str());
  char* buffer_ptr = const_cast<char*>(buffer_str.c_str());

  int result = yaml_file_read_handler(data_ptr, buffer_ptr, size_read,
                                     const_cast<size_t*>(&size_read));
  return result;
}