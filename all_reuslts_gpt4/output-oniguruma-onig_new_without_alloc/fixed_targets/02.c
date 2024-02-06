#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    onig_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);

  OnigErrorInfo einfo;
  OnigEncoding enc = ONIG_ENCODING_UTF8;
  OnigSyntaxType* syntax = ONIG_SYNTAX_DEFAULT;
  int option = ONIG_OPTION_NONE;

  size_t pattern_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  std::string pattern = provider.ConsumeBytesAsString(pattern_size);
  char* pattern_end = const_cast<char*>(pattern.c_str()) + pattern.size();

  re_pattern_buffer* reg = onig_alloc_pattern_buffer();
  if (reg == nullptr) {
    return 0;
  }

  int ret = onig_new_without_alloc(reg, const_cast<char*>(pattern.c_str()), pattern_end, option, enc, syntax, &einfo);

  onig_free_pattern_buffer(reg);

  return 0;
}