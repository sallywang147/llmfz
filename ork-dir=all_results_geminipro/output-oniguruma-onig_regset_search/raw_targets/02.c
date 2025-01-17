#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string pattern = stream.ConsumeRemainingBytesAsString();
  OnigRegSetStruct* set = onig_regset_new();
  if (set == nullptr) {
    return 0;
  }
  const int error = onig_regset_compile(set, pattern.c_str(), pattern.c_str() + pattern.size(), ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8,
                                        ONIG_SYNTAX_DEFAULT, &error);
  if (error != ONIG_NORMAL) {
    onig_regset_delete(set);
    return 0;
  }
  const std::string text = stream.ConsumeRemainingBytesAsString();
  int rmatch_pos[2];
  const int result = onig_regset_search(set, text.c_str(), text.c_str() + text.size(), text.c_str(), text.c_str() + text.size(), 0, ONIG_OPTION_DEFAULT, rmatch_pos);
  onig_regset_delete(set);
  return result;
}