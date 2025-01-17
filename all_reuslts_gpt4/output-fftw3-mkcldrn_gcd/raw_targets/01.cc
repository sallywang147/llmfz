#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>
#include <string>

struct problem_rdft {
  size_t size;
  double* in;
  double* out;
};

struct planner_s {
  int rank;
  int flags;
};

struct P_s {
  int id;
  int type;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t problem_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  std::vector<double> in(problem_size, stream.ConsumeFloatingPoint<double>());
  std::vector<double> out(problem_size, stream.ConsumeFloatingPoint<double>());

  problem_rdft p = {problem_size, in.data(), out.data()};

  planner_s plnr = {stream.ConsumeIntegral<int>(), stream.ConsumeIntegral<int>()};

  P_s ego = {stream.ConsumeIntegral<int>(), stream.ConsumeIntegral<int>()};

  mkcldrn_gcd(&p, &plnr, &ego);

  return 0;
}