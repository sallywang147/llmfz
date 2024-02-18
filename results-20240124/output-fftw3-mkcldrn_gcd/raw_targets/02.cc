 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "problem_rdft.h"
#include "planner.h"
#include "P.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct problem_rdft problem_rdft;
  struct planner_s planner_s;
  struct P_s P_s;

  problem_rdft.N = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_min = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_max = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_max_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step_step = stream.ConsumeIntegral<uint64_t>();
  problem_rdft.n_min_step_step_step_