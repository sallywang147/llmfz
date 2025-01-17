#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Define and initialize the required parameters for the mkcldrn_cut function
  struct problem_rdft p;
  struct planner_s plnr;
  struct P_s ego;

  // Consume data from the fuzzer input
  p.sz = stream.ConsumeIntegral<int>();
  p.vecsz = stream.ConsumeIntegral<int>();
  p.I = stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  p.O = stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  p.kind = (rdft_kind)stream.ConsumeIntegral<int>();

  plnr.adt = stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  plnr.problem_alloc = (problem *(*)(planner *, const problem *))stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  plnr.problem_destroy = (void (*)(problem *))stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  plnr.ops.other = stream.ConsumeIntegral<int>();
  plnr.ops.add = stream.ConsumeIntegral<int>();
  plnr.ops.mul = stream.ConsumeIntegral<int>();
  plnr.ops.fma = stream.ConsumeIntegral<int>();
  plnr.cost_hook = (double (*)(const problem *, double))stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  plnr.cost_guess = stream.ConsumeFloatingPoint<double>();
  plnr.cost_max = stream.ConsumeFloatingPoint<double>();
  plnr.timelimit_impatience = stream.ConsumeIntegral<int>();
  plnr.timelimit_gap = stream.ConsumeIntegral<int>();
  plnr.timelimit = stream.ConsumeIntegral<int>();
  plnr.sadt = stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();

  ego.rdft_apply = (void (*)(plan *, float *, float *))stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  ego.apply = (void (*)(plan *, float *, float *))stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  ego.problem = (problem *)stream.ConsumeBytes<unsigned char>(stream.ConsumeIntegralInRange(0, size)).data();
  ego.ops.other = stream.ConsumeIntegral<int>();
  ego.ops.add = stream.ConsumeIntegral<int>();
  ego.ops.mul = stream.ConsumeIntegral<int>();
  ego.ops.fma = stream.ConsumeIntegral<int>();
  ego.could_prune_now_p = stream.ConsumeBool();
  ego.cpu_cost = stream.ConsumeFloatingPoint<double>();
  ego.flops = stream.ConsumeFloatingPoint<double>();
  ego.i = stream.ConsumeIntegral<int>();
  ego.t = stream.ConsumeFloatingPoint<double>();
  ego.need_buffering_p = stream.ConsumeBool();
  ego.could_buffer_self_p = stream.ConsumeBool();
  ego.kind = (rdft_kind)stream.ConsumeIntegral<int>();

  // Call the function with the initialized parameters
  int result = mkcldrn_cut(&p, &plnr, &ego);

  return 0;
}