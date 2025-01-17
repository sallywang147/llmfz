#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "rdft/rdft.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  problem_rdft problem_rdft;
  planner_s planner_s;
  P_s P_s;

  mkcldrn_cut(&problem_rdft, &planner_s, &P_s);

  return 0;
}