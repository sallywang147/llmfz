#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "oniguruma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  char* str = (char*)stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size/3)).c_str();
  char* end = (char*)stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size/3)).c_str();
  char* start = (char*)stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, size/3)).c_str();
  char* range = (char*)stream.ConsumeRemainingBytesAsString().c_str();

  int lead = stream.ConsumeIntegral<int>();
  int option = stream.ConsumeIntegral<int>();
  int rmatch_pos = stream.ConsumeIntegral<int>();

  OnigMatchParamStruct* mps[1];
  mps[0] = onig_new_match_param();
  if (mps[0] == NULL) {
    return 0;
  }

  OnigRegSetStruct* set = onig_regset_alloc(1, mps);
  if (set == NULL) {
    onig_free_match_param(mps[0]);
    return 0;
  }

  int ret = onig_regset_search_with_param(set, str, end, start, range, lead, option, mps, &rmatch_pos);

  onig_regset_free(set);
  onig_free_match_param(mps[0]);

  return 0;
}