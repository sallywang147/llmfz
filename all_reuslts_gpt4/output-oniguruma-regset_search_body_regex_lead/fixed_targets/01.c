#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  OnigRegSetStruct *set = nullptr;
  OnigMatchParamStruct *mps = nullptr;
  int rmatch_pos = 0;

  std::string str = fuzzed_data.ConsumeBytesAsString(fuzzed_data.ConsumeIntegralInRange<size_t>(0, size / 2));
  std::string end = str + str.length();
  std::string start = str;
  std::string orig_range = str;

  int lead = fuzzed_data.ConsumeIntegral<int>();
  int option = fuzzed_data.ConsumeIntegral<int>();

  regset_search_body_regex_lead(set, const_cast<char*>(str.c_str()), const_cast<char*>(end.c_str()), const_cast<char*>(start.c_str()), const_cast<char*>(orig_range.c_str()), lead, option, &mps, &rmatch_pos);

  return 0;
}