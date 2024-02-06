#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the regex buffer
  struct re_pattern_buffer reg;
  onig_initialize(&reg, ONIG_ENCODING_UTF8);

  // Extract the pattern string
  std::string pattern = stream.ConsumeRandomLengthString();
  char* pattern_end = pattern.end().base();

  // Extract the option
  int option = stream.ConsumeIntegral<int>();

  // Set the encoding and syntax
  struct OnigEncodingTypeST* enc = ONIG_ENCODING_UTF8;
  struct OnigSyntaxType* syntax = ONIG_SYNTAX_DEFAULT;

  // Initialize the error info
  struct OnigErrorInfo einfo;

  // Call the function
  int ret = onig_new_without_alloc(&reg, pattern.data(), pattern_end, option, enc, syntax, &einfo);

  onig_end();

  return 0;
}