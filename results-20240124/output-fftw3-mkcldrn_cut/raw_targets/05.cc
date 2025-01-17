 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct problem_rdft problem_rdft;
  struct planner_s planner_s;
  struct P_s P_s;

  int ret = mkcldrn_cut(&problem_rdft, &planner_s, &P_s);

  return 0;
}