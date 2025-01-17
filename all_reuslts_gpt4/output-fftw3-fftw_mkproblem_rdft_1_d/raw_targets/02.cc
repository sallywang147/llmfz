#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  FuzzedDataProvider stream(data, size);
  uint8_t ARRAY_SIZE = stream.ConsumeIntegralInRange<uint8_t>(1, 250);
  
  if ((ARRAY_SIZE * sizeof(double) * 2) > size) {
    return 0;
  }
  double signal[ARRAY_SIZE];
  double result[ARRAY_SIZE];

  // Seed the signals with fuzz data
  for (int i = 0; i < ARRAY_SIZE; ++i) {
    signal[i] = stream.ConsumeFloatingPoint<double>();
  }

  struct tensor sz = {ARRAY_SIZE, 1, {ARRAY_SIZE, 1}};
  struct tensor vecsz = {ARRAY_SIZE, 1, {ARRAY_SIZE, 1}};

  int kind = stream.ConsumeIntegral<int>();

  struct problem_s * problem = fftw_mkproblem_rdft_1_d(&sz, &vecsz, signal, result, kind);

  fftw_plan plan = fftw_plan_dft_1d(ARRAY_SIZE, signal, result, FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(plan);
  fftw_destroy_plan(plan);

  return 0;
}