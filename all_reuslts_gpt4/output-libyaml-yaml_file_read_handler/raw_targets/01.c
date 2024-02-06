#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int yaml_file_read_handler(char * data, char * buffer, size_t size, size_t * size_read);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for the data parameter
  std::string str_data = stream.ConsumeRandomLengthString();
  char *data_ptr = const_cast<char *>(str_data.c_str());

  // Extract a string for the buffer parameter
  std::string str_buffer = stream.ConsumeRandomLengthString();
  char *buffer_ptr = const_cast<char *>(str_buffer.c_str());

  // Extract a size for the size parameter
  size_t size_arg = stream.ConsumeIntegral<size_t>();

  // Initialize size_read
  size_t size_read = 0;

  // Call the function
  yaml_file_read_handler(data_ptr, buffer_ptr, size_arg, &size_read);

  return 0;
}