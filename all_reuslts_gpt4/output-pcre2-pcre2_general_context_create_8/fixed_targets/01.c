#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pcre2.h"

// Define the function types for private_malloc and private_free
typedef void *(*func_type)(size_t);

// Implement private_malloc and private_free
void *private_malloc(size_t size) {
  return malloc(size);
}

void private_free(void *ptr) {
  free(ptr);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string memory_data_str = stream.ConsumeRandomLengthString();
  char *memory_data = const_cast<char*>(memory_data_str.c_str());

  // Call the function to fuzz
  struct pcre2_real_general_context_8 *context = pcre2_general_context_create_8(private_malloc, private_free, memory_data);
  
  // Free the context after use
  pcre2_general_context_free_8(context);

  return 0;
}