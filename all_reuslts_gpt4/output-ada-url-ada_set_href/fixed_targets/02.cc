#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern bool ada_set_href(char * result, char * input, size_t length);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Prepare a buffer for the result
  char result[256];
  memset(result, 0, sizeof(result));

  // Extract a string from the stream
  std::string input = stream.ConsumeRemainingBytesAsString();
  
  // Call the target function
  ada_set_href(result, const_cast<char*>(input.c_str()), input.size());

  return 0;
}