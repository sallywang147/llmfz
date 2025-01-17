#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "mkcldrn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct problem_rdft problem;
  struct planner_s planner;
  struct P_s ego;

  memset(&problem, 0, sizeof(problem));
  memset(&planner, 0, sizeof(planner));
  memset(&ego, 0, sizeof(ego));

  problem.n = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_2_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_3_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_4_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_5_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_6_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_7_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_8_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_9_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_10_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_11_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_12_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_13_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_14_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  problem.i_15_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);

  planner.max_depth = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_width = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_cuts = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops_per_cut = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops_per_depth = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops_per_width = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops_per_cut_depth = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops_per_cut_width = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops_per_depth_width = stream.ConsumeIntegralInRange<int>(1, 1000);
  planner.max_ops_per_cut_depth_width = stream.ConsumeIntegralInRange<int>(1, 1000);

  ego.n = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_2_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_3_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_4_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_5_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_6_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_7_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_8_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_9_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_10_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_11_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_12_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_13_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_14_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);
  ego.i_15_n_k = stream.ConsumeIntegralInRange<int>(1, 1000);

  int result = mkcldrn_cut(&problem, &planner, &ego);

  return result;
}