#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int png_image_read_direct(char * argument);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char *>(str.c_str());

  // Call the function with the fuzzed input
  png_image_read_direct(ptr);

  return 0;
}