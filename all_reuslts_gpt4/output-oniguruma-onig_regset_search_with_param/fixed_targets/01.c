#include <fuzzer/FuzzedDataProvider.h>
#include <oniguruma.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  OnigErrorInfo einfo;
  OnigEncoding use_encs[] = { ONIG_ENCODING_UTF8 };
  OnigOptionType options = ONIG_OPTION_NONE;

  const std::string pattern = stream.ConsumeRandomLengthString();
  OnigRegex regex;
  int r = onig_new(&regex, (unsigned char*)pattern.c_str(),
                   (unsigned char*)(pattern.c_str() + pattern.size()),
                   options, ONIG_ENCODING_UTF8, ONIG_SYNTAX_DEFAULT, &einfo);
  if (r != ONIG_NORMAL) {
    return 0;
  }

  const std::string str = stream.ConsumeRemainingBytesAsString();
  char* start = (char*)str.c_str();
  char* range = (char*)str.c_str() + str.size();
  char* end = range;

  OnigRegion* region = onig_region_new();
  if (!region) {
    onig_free(regex);
    return 0;
  }

  struct OnigRegSetStruct* regset = onig_regset_new(&regex, 1);
  if (!regset) {
    onig_region_free(region, 1);
    onig_free(regex);
    return 0;
  }

  int lead = stream.ConsumeIntegral<int>();
  struct OnigMatchParamStruct* mps = onig_match_param_new();
  if (!mps) {
    onig_regset_free(regset);
    onig_region_free(region, 1);
    onig_free(regex);
    return 0;
  }

  int rmatch_pos;
  r = onig_regset_search_with_param(regset, (unsigned char*)start,
                                    (unsigned char*)end, (unsigned char*)start,
                                    (unsigned char*)range, lead, options, &mps,
                                    &rmatch_pos);
  onig_match_param_free(mps);
  onig_regset_free(regset);
  onig_region_free(region, 1);
  onig_free(regex);
  return 0;
}