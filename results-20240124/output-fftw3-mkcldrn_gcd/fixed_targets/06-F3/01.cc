#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "mkcldrn.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct problem_rdft problem;
  struct planner_s planner;
  struct P_s ego;

  FuzzedDataProvider provider(data, size);
  problem.n = provider.ConsumeIntegral<uint32_t>();
  problem.m = provider.ConsumeIntegral<uint32_t>();
  problem.k = provider.ConsumeIntegral<uint32_t>();
  problem.n1 = provider.ConsumeIntegral<uint32_t>();
  problem.m1 = provider.ConsumeIntegral<uint32_t>();
  problem.k1 = provider.ConsumeIntegral<uint32_t>();
  problem.n2 = provider.ConsumeIntegral<uint32_t>();
  problem.m2 = provider.ConsumeIntegral<uint32_t>();
  problem.k2 = provider.ConsumeIntegral<uint32_t>();
  problem.n3 = provider.ConsumeIntegral<uint32_t>();
  problem.m3 = provider.ConsumeIntegral<uint32_t>();
  problem.k3 = provider.ConsumeIntegral<uint32_t>();
  problem.n4 = provider.ConsumeIntegral<uint32_t>();
  problem.m4 = provider.ConsumeIntegral<uint32_t>();
  problem.k4 = provider.ConsumeIntegral<uint32_t>();
  problem.n5 = provider.ConsumeIntegral<uint32_t>();
  problem.m5 = provider.ConsumeIntegral<uint32_t>();
  problem.k5 = provider.ConsumeIntegral<uint32_t>();
  problem.n6 = provider.ConsumeIntegral<uint32_t>();
  problem.m6 = provider.ConsumeIntegral<uint32_t>();
  problem.k6 = provider.ConsumeIntegral<uint32_t>();
  problem.n7 = provider.ConsumeIntegral<uint32_t>();
  problem.m7 = provider.ConsumeIntegral<uint32_t>();
  problem.k7 = provider.ConsumeIntegral<uint32_t>();
  problem.n8 = provider.ConsumeIntegral<uint32_t>();
  problem.m8 = provider.ConsumeIntegral<uint32_t>();
  problem.k8 = provider.ConsumeIntegral<uint32_t>();
  problem.n9 = provider.ConsumeIntegral<uint32_t>();
  problem.m9 = provider.ConsumeIntegral<uint32_t>();
  problem.k9 = provider.ConsumeIntegral<uint32_t>();
  problem.n10 = provider.ConsumeIntegral<uint32_t>();
  problem.m10 = provider.ConsumeIntegral<uint32_t>();
  problem.k10 = provider.ConsumeIntegral<uint32_t>();
  problem.n11 = provider.ConsumeIntegral<uint32_t>();
  problem.m11 = provider.ConsumeIntegral<uint32_t>();
  problem.k11 = provider.ConsumeIntegral<uint32_t>();
  problem.n12 = provider.ConsumeIntegral<uint32_t>();
  problem.m12 = provider.ConsumeIntegral<uint32_t>();
  problem.k12 = provider.ConsumeIntegral<uint32_t>();
  problem.n13 = provider.ConsumeIntegral<uint32_t>();
  problem.m13 = provider.ConsumeIntegral<uint32_t>();
  problem.k13 = provider.ConsumeIntegral<uint32_t>();
  problem.n14 = provider.ConsumeIntegral<uint32_t>();
  problem.m14 = provider.ConsumeIntegral<uint32_t>();
  problem.k14 = provider.ConsumeIntegral<uint32_t>();
  problem.n15 = provider.ConsumeIntegral<uint32_t>();
  problem.m15 = provider.ConsumeIntegral<uint32_t>();
  problem.k15 = provider.ConsumeIntegral<uint32_t>();
  problem.n16 = provider.ConsumeIntegral<uint32_t>();
  problem.m16 = provider.ConsumeIntegral<uint32_t>();
  problem.k16 = provider.ConsumeIntegral<uint32_t>();
  problem.n17 = provider.ConsumeIntegral<uint32_t>();
  problem.m17 = provider.ConsumeIntegral<uint32_t>();
  problem.k17 = provider.ConsumeIntegral<uint32_t>();
  problem.n18 = provider.ConsumeIntegral<uint32_t>();
  problem.m18 = provider.ConsumeIntegral<uint32_t>();
  problem.k18 = provider.ConsumeIntegral<uint32_t>();
  problem.n19 = provider.ConsumeIntegral<uint32_t>();
  problem.m19 = provider.ConsumeIntegral<uint32_t>();
  problem.k19 = provider.ConsumeIntegral<uint32_t>();
  problem.n20 = provider.ConsumeIntegral<uint32_t>();
  problem.m20 = provider.ConsumeIntegral<uint32_t>();
  problem.k20 = provider.ConsumeIntegral<uint32_t>();
  problem.n21 = provider.ConsumeIntegral<uint32_t>();
  problem.m21 = provider.ConsumeIntegral<uint32_t>();
  problem.k21 = provider.ConsumeIntegral<uint32_t>();
  problem.n22 = provider.ConsumeIntegral<uint32_t>();
  problem.m22 = provider.ConsumeIntegral<uint32_t>();
  problem.k22 = provider.ConsumeIntegral<uint32_t>();
  problem.n23 = provider.ConsumeIntegral<uint32_t>();
  problem.m23 = provider.ConsumeIntegral<uint32_t>();
  problem.k23 = provider.ConsumeIntegral<uint32_t>();
  problem.n24 = provider.ConsumeIntegral<uint32_t>();
  problem.m24 = provider.ConsumeIntegral<uint32_t>();
  problem.k24 = provider.ConsumeIntegral<uint32_t>();
  problem.n25 = provider.ConsumeIntegral<uint32_t>();
  problem.m25 = provider.ConsumeIntegral<uint32_t>();
  problem.k25 = provider.ConsumeIntegral<uint32_t>();
  problem.n26 = provider.ConsumeIntegral<uint32_t>();
  problem.m26 = provider.ConsumeIntegral<uint32_t>();
  problem.k26 = provider.ConsumeIntegral<uint32_t>();
  problem.n27 = provider.ConsumeIntegral<uint32_t>();
  problem.m27 = provider.ConsumeIntegral<uint32_t>();
  problem.k27 = provider.ConsumeIntegral<uint32_t>();
  problem.n28 = provider.ConsumeIntegral<uint32_t>();
  problem.m28 = provider.ConsumeIntegral<uint32_t>();
  problem.k28 = provider.ConsumeIntegral<uint32_t>();
  problem.n29 = provider.ConsumeIntegral<uint32_t>();
  problem.m29 = provider.ConsumeIntegral<uint32_t>();
  problem.k29 = provider.ConsumeIntegral<uint32_t>();
  problem.n30 = provider.ConsumeIntegral<uint32_t>();
  problem.m30 = provider.ConsumeIntegral<uint32_t>();
  problem.k30 = provider.ConsumeIntegral<uint32_t>();
  problem.n31 = provider.ConsumeIntegral<uint32_t>();
  problem.m31 = provider.ConsumeIntegral<uint32_t>();
  problem.k31 = provider.ConsumeIntegral<uint32_t>();
  problem.n32 = provider.ConsumeIntegral<uint32_t>();
  problem.m32 = provider.ConsumeIntegral<uint32_t>();
  problem.k32 = provider.ConsumeIntegral<uint32_t>();

  int ret = mkcldrn_gcd(&problem, &planner, &ego);
  if (ret != 0) {
    return 0;
  }
  return 0;
}