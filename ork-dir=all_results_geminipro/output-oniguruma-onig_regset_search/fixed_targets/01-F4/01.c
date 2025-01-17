#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "oniguruma.h"

extern "C" {
#include <onig/oniguruma.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string text = stream.ConsumeRemainingBytesAsString();
  const std::string pattern = stream.ConsumeRemainingBytesAsString();

  OnigRegSetStruct* regset = onig_regset_new();
  if (regset == nullptr) {
    return 0;
  }

  OnigRegex* regex = onig_new(reinterpret_cast<const OnigUChar*>(pattern.c_str()),
                               pattern.size(),
                               ONIG_OPTION_DEFAULT,
                               ONIG_ENCODING_UTF8,
                               ONIG_SYNTAX_DEFAULT,
                               nullptr,
                               nullptr);
  if (regex == nullptr) {
    onig_regset_free(regset);
    return 0;
  }

  int rmatch_pos[10];
  int rmatch_pos_size = sizeof(rmatch_pos) / sizeof(rmatch_pos[0]);
  int ret = onig_regset_search(regset, regex,
                               reinterpret_cast<const OnigUChar*>(text.c_str()),
                               text.size(),
                               0,
                               text.size(),
                               ONIG_OPTION_DEFAULT,
                               rmatch_pos,
                               rmatch_pos_size);
  if (ret < 0) {
    onig_regset_free(regset);
    onig_free(regex);
    return 0;
  }

  onig_regset_free(regset);
  onig_free(regex);
  return 0;
}