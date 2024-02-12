#include <fftw3.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct problem_rdft p;
  struct planner_s plnr;
  struct P_s ego;

  p.n = stream.ConsumeIntegral<int>();
  p.m = stream.ConsumeIntegral<int>();
  p.k = stream.ConsumeIntegral<int>();
  p.l = stream.ConsumeIntegral<int>();
  p.r = stream.ConsumeIntegral<int>();
  p.s = stream.ConsumeIntegral<int>();
  p.t = stream.ConsumeIntegral<int>();
  p.u = stream.ConsumeIntegral<int>();

  plnr.n = stream.ConsumeIntegral<int>();
  plnr.m = stream.ConsumeIntegral<int>();
  plnr.k = stream.ConsumeIntegral<int>();
  plnr.l = stream.ConsumeIntegral<int>();
  plnr.r = stream.ConsumeIntegral<int>();
  plnr.s = stream.ConsumeIntegral<int>();
  plnr.t = stream.ConsumeIntegral<int>();
  plnr.u = stream.ConsumeIntegral<int>();

  ego.n = stream.ConsumeIntegral<int>();
  ego.m = stream.ConsumeIntegral<int>();
  ego.k = stream.ConsumeIntegral<int>();
  ego.l = stream.ConsumeIntegral<int>();
  ego.r = stream.ConsumeIntegral<int>();
  ego.s = stream.ConsumeIntegral<int>();
  ego.t = stream.ConsumeIntegral<int>();
  ego.u = stream.ConsumeIntegral<int>();

  int mkcldrn_gcd_result = mkcldrn_gcd(&p, &plnr, &ego);

  return mkcldrn_gcd_result;
}