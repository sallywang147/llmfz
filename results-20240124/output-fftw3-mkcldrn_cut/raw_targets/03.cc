 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "mkcldrn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct problem_rdft p;
  memset(&p, 0, sizeof(p));

  struct planner_s plnr;
  memset(&plnr, 0, sizeof(plnr));

  struct P_s ego;
  memset(&ego, 0, sizeof(ego));

  int ret = mkcldrn_cut(&p, &plnr, &ego);

  return 0;
}