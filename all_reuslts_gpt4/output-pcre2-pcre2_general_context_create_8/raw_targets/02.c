#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "pcre2.h"

// Custom memory management functions
void* custom_malloc(size_t size) {
  return malloc(size);
}

void custom_free(void* ptr) {
  free(ptr);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string memory_data = stream.ConsumeRandomLengthString();
  char *memory_data_ptr = const_cast<char*>(memory_data.c_str());

  // Call the target function
  pcre2_general_context_create_8(custom_malloc, custom_free, memory_data_ptr);

  return 0;
}