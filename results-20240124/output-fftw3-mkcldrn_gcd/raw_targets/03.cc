 #include <fuzzer/FuzzedDataProvider.h>
#include "mkcldrn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct problem_rdft p;
  struct planner_s plnr;
  struct P_s ego;
  mkcldrn_gcd(&p, &plnr, &ego);
  return 0;
}