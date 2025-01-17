#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the compile context
  pcre2_real_compile_context_8* ccontext = pcre2_compile_context_create_8(NULL);
  if (ccontext == NULL) {
    return 0;
  }

  // Extract an integer for the newline parameter
  int newline = stream.ConsumeIntegral<int>();

  // Call the target function
  int result = pcre2_set_newline_8(ccontext, newline);

  // Clean up
  pcre2_compile_context_free_8(ccontext);

  return 0;
}