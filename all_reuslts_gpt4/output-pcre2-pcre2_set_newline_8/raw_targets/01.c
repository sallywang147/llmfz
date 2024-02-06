#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "pcre2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  pcre2_compile_context *ccontext = pcre2_compile_context_create(NULL);
  if (ccontext == NULL) {
    // Out of memory
    return 0;
  }

  // Define a list of valid newline constants
  const std::vector<int> newlines = {PCRE2_NEWLINE_CR, PCRE2_NEWLINE_LF, PCRE2_NEWLINE_CRLF, PCRE2_NEWLINE_ANY, PCRE2_NEWLINE_ANYCRLF, PCRE2_NEWLINE_NUL};

  // Pick a random newline constant
  int newline = stream.PickValueInArray(newlines);

  // Call the function to fuzz
  int result = pcre2_set_newline_8(ccontext, newline);

  pcre2_compile_context_free(ccontext);

  return 0;
}