#include <fftw3.h>
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
  static bool initialized = false;
  if (!initialized) {
    mkcldrn_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  struct problem_rdft p;
  struct planner_s plnr;
  struct P_s ego;
  mkcldrn_cut(&p, &plnr, &ego);
  return 0;
}