#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "oniguruma.h"

extern "C" {
#include "regset.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();

  OnigRegSetStruct* set = onig_regset_new();
  if (set == nullptr) {
    return 0;
  }
  OnigMatchParamStruct* mps = onig_match_param_new();
  if (mps == nullptr) {
    onig_regset_delete(set);
    return 0;
  }

  int rmatch_pos = 0;
  int lead = stream.ConsumeIntegral<int>();
  int option = stream.ConsumeIntegral<int>();
  int ret = regset_search_body_regex_lead(
      set, input.c_str(), input.c_str() + input.size(), input.c_str(),
      input.c_str(), lead, option, &mps, &rmatch_pos);
  if (ret == ONIG_MISMATCH) {
    onig_match_param_free(mps);
    onig_regset_delete(set);
    return 0;
  }

  onig_match_param_free(mps);
  onig_regset_delete(set);
  return 0;
}