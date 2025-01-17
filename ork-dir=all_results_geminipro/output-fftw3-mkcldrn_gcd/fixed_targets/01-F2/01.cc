#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "mkcldrn.h"
#include "mkcldrn_gcd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  uint32_t n = provider.ConsumeIntegral<uint32_t>();
  uint32_t m = provider.ConsumeIntegral<uint32_t>();
  uint32_t k = provider.ConsumeIntegral<uint32_t>();
  uint32_t l = provider.ConsumeIntegral<uint32_t>();
  uint32_t p = provider.ConsumeIntegral<uint32_t>();
  uint32_t q = provider.ConsumeIntegral<uint32_t>();

  struct problem_rdft p_rdft;
  p_rdft.n = n;
  p_rdft.m = m;
  p_rdft.k = k;
  p_rdft.l = l;
  p_rdft.p = p;
  p_rdft.q = q;

  struct planner_s plnr;
  struct P_s ego;

  int ret = mkcldrn_gcd(&p_rdft, &plnr, &ego);
  if (ret == 0) {
    printf("mkcldrn_gcd returned 0\n");
  } else {
    printf("mkcldrn_gcd returned %d\n", ret);
  }

  return 0;
}