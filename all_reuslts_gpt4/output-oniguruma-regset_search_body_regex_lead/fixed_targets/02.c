#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  OnigErrorInfo einfo;
  OnigRegex regex;
  OnigRegion *region;

  const std::string pattern = stream.ConsumeRandomLengthString();
  const std::string str = stream.ConsumeRemainingBytesAsString();

  char* pattern_c_str = const_cast<char*>(pattern.c_str());
  char* str_c_str = const_cast<char*>(str.c_str());

  int r = onig_new(&regex, (OnigUChar*)pattern_c_str, (OnigUChar*)(pattern_c_str + pattern.size()),
                   ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &einfo);
  if (r != ONIG_NORMAL) {
    return 0;
  }

  region = onig_region_new();

  struct OnigRegSetStruct* set;
  int set_num = 1;
  OnigRegex* regs = &regex;
  r = onig_regset_new(&set, set_num, &regs);
  if (r != ONIG_NORMAL) {
    onig_free(regex);
    onig_region_free(region, 1);
    return 0;
  }

  struct OnigMatchParamStruct** mps;
  r = onig_regset_make_match_param_with_region(set, &mps, region);
  if (r != ONIG_NORMAL) {
    onig_regset_free(set);
    onig_free(regex);
    onig_region_free(region, 1);
    return 0;
  }

  int rmatch_pos = 0;
  r = regset_search_body_regex_lead(set, str_c_str, str_c_str + str.size(), str_c_str, str_c_str + str.size(), 0, ONIG_OPTION_DEFAULT, mps, &rmatch_pos);

  onig_regset_free(set);
  onig_free(regex);
  onig_region_free(region, 1);
  return 0;
}