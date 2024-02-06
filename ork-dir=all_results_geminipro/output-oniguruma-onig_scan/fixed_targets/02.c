#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "onig/onig.h"

extern "C" {
#include "onig/oniguruma.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string regex = stream.ConsumeRemainingBytesAsString();
  const std::string input = stream.ConsumeRemainingBytesAsString();

  onig_regex_t* reg;
  onig_error_info einfo;
  const OnigUChar* pattern = reinterpret_cast<const OnigUChar*>(regex.c_str());
  const OnigUChar* end = pattern + regex.size();
  int r = onig_new(&reg, pattern, end, ONIG_OPTION_DEFAULT, ONIG_ENCODING_UTF8,
                  ONIG_SYNTAX_DEFAULT, &einfo);
  if (r != ONIG_NORMAL) {
    return 0;
  }

  onig_region* region = onig_region_new();

  // Fix: Use onig_search instead of onig_scan.
  r = onig_search(reg, reinterpret_cast<const OnigUChar*>(input.c_str()),
                reinterpret_cast<const OnigUChar*>(input.c_str() + input.size()),
                region, ONIG_OPTION_NONE);
  if (r >= 0) {
    // Success.
  }

  onig_region_free(region, 1 /* free self */);
  onig_free(reg);
  return 0;
}