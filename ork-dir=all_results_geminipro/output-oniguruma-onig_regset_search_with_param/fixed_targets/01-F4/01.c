#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "oniguruma.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();
  const std::string pattern = stream.ConsumeRemainingBytesAsString();

  OnigRegSetStruct* set = onig_regset_new();
  if (set == nullptr) {
    return 0;
  }
  OnigErrorInfo error_info;
  const OnigOptionType options = ONIG_OPTION_DEFAULT;
  const OnigEncodingType encoding = ONIG_ENCODING_UTF8;
  if (onig_regset_compile(set, pattern.c_str(), pattern.size(), options,
                          encoding, &error_info) != ONIG_NORMAL) {
    onig_regset_free(set);
    return 0;
  }

  OnigMatchParamStruct* mps = onig_match_param_new();
  if (mps == nullptr) {
    onig_regset_free(set);
    return 0;
  }

  int rmatch_pos = 0;
  const int r = onig_regset_search_with_param(set, input.c_str(),
                                             input.c_str() + input.size(),
                                             input.c_str(),
                                             input.c_str() + input.size(), 0,
                                             options, &mps, &rmatch_pos);
  onig_match_param_free(mps);
  onig_regset_free(set);
  return r;
}