#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

extern "C" {
#include <png.h>
}

extern "C" png_uint_32 LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a random string of up to 1024 characters.
  const size_t max_string_length = 1024;
  char* argument = new char[max_string_length + 1];
  stream.ConsumeBytes(argument, max_string_length);
  argument[max_string_length] = '\0';

  // Call the function under test.
  png_uint_32 result = png_image_read_colormapped(argument);

  // Clean up.
  delete[] argument;

  return result;
}