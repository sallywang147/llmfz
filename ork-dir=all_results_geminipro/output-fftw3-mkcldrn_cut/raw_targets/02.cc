#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the problem_rdft struct.
  struct problem_rdft p;
  p.n = stream.ConsumeIntegralInRange<int>(1, 10000);
  p.isign = stream.ConsumeIntegralInRange<int>(-1, 1);
  p.scale = stream.ConsumeFloatingPoint<double>();

  // Initialize the planner_s struct.
  struct planner_s plnr;
  plnr.max_threads = stream.ConsumeIntegralInRange<int>(1, 100);
  plnr.flags = stream.ConsumeIntegralInRange<int>(0, 100);

  // Initialize the P_s struct.
  struct P_s ego;
  ego.n = stream.ConsumeIntegralInRange<int>(1, 10000);
  ego.isign = stream.ConsumeIntegralInRange<int>(-1, 1);
  ego.scale = stream.ConsumeFloatingPoint<double>();

  // Call the mkcldrn_cut function.
  int result = mkcldrn_cut(&p, &plnr, &ego);

  // Consume the remaining bytes.
  stream.ConsumeRemainingBytes();

  return result;
}