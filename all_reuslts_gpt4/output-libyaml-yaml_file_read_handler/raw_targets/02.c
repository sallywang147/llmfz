#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string data_str = stream.ConsumeRandomLengthString();
  char *data_ptr = data_str.c_str();

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> buffer(buffer_size);
  
  size_t size_read = 0;

  yaml_file_read_handler(data_ptr, buffer.data(), buffer_size, &size_read);

  return 0;
}