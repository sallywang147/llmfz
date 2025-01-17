#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string regex = stream.ConsumeRemainingBytesAsString();
  OnigRegSetStruct* set = onig_regset_new();
  if (set == nullptr) {
    return 0;
  }
  const int r = onig_regset_compile(set, regex.c_str(), regex.c_str() + regex.size(),
                                  ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8,
                                  ONIG_SYNTAX_DEFAULT, &stream);
  if (r != ONIG_NORMAL) {
    onig_regset_delete(set);
    return 0;
  }
  const std::string text = stream.ConsumeRemainingBytesAsString();
  OnigMatchParamStruct* mps = onig_match_param_new();
  int rmatch_pos[10];
  const int r2 = onig_regset_search_with_param(set, text.c_str(),
                                             text.c_str() + text.size(),
                                             text.c_str(), text.c_str() + text.size(),
                                             ONIG_OFFSET_BY_INDEX, ONIG_OPTION_DEFAULT,
                                             &mps, rmatch_pos);
  onig_match_param_free(mps);
  onig_regset_delete(set);
  return 0;
}