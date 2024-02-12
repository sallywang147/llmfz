#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "mkcldrn.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct problem_rdft problem;
  problem.n = provider.ConsumeIntegralInRange<uint32_t>(1, 100000);
  problem.m = provider.ConsumeIntegralInRange<uint32_t>(1, 100000);
  problem.k = provider.ConsumeIntegralInRange<uint32_t>(1, 100000);
  problem.l = provider.ConsumeIntegralInRange<uint32_t>(1, 100000);
  problem.r = provider.ConsumeIntegralInRange<uint32_t>(1, 100000);
  problem.s = provider.ConsumeIntegralInRange<uint32_t>(1, 100000);
  struct planner_s planner;
  struct P_s ego;
  mkcldrn_gcd(&problem, &planner, &ego);
  return 0;
}