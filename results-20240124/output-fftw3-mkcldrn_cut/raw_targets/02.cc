 #include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mkcldrn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct problem_rdft problem;
  struct planner_s planner;
  struct P_s ego;

  mkcldrn_init(&problem, &planner, &ego);
  mkcldrn_cut(&problem, &planner, &ego);

  return 0;
}