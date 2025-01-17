#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern bool ada_set_href(char * result, char * input, size_t length);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Consume a string for the input parameter.
  std::string input = provider.ConsumeRandomLengthString();
  char* input_ptr = const_cast<char*>(input.c_str());

  // Consume the remaining bytes for the result parameter.
  std::string result = provider.ConsumeRemainingBytesAsString();
  char* result_ptr = const_cast<char*>(result.c_str());

  // Call the function under test.
  ada_set_href(result_ptr, input_ptr, input.size());

  return 0;
}