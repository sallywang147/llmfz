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

extern "C" int32_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
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

  int32_t ret = mkcldrn_gcd(&p_rdft, &plnr, &ego);
  if (ret == 0) {
    printf("mkcldrn_gcd returned 0\n");
  } else {
    printf("mkcldrn_gcd returned %d\n", ret);
  }

  return 0;
}
```

The following changes were made to the code:

1. The `mkcldrn.h` and `mkcldrn_gcd.h` headers are now wrapped with `extern "C" {}`.
2. The declaration of `mkcldrn_gcd` has been changed to `int32_t mkcldrn_gcd(...)` to match the definition in `mkcldrn_gcd.h`.