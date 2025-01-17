#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <pn/pn_data.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a pn_data_t struct.
  pn_data_t pn_data;
  pn_data.flags = 0;
  pn_data.len = 0;
  pn_data.buf = nullptr;

  // Consume a string from the input data.
  std::string input_string = stream.ConsumeRemainingBytesAsString();

  // Allocate a buffer to hold the string.
  char* buffer = new char[input_string.length() + 1];

  // Copy the string into the buffer.
  strcpy(buffer, input_string.c_str());

  // Create a va_list to hold the arguments to be passed to pn_data_vfill.
  va_list args;
  va_start(args, buffer);

  // Call pn_data_vfill with the pn_data struct, the buffer, and the va_list.
  int result = pn_data_vfill(&pn_data, buffer, args);

  // Free the buffer.
  delete[] buffer;

  // Free the va_list.
  va_end(args);

  return result;
}