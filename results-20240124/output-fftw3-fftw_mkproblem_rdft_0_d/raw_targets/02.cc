 #include <fftw3.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // For reference, fftw_compelx is defined:
  // typedef double fftw_complex[2]
  if (size < 1) {
    return 0;
  }
  uint8_t ARRAY_SIZE = (*data) % 250 + 1;
  data++;
  size -= 1;
  if ((ARRAY_SIZE * sizeof(double) * 2) > size) {
    return 0;
  }
  fftw_complex signal[ARRAY_SIZE];
  fftw_complex result[ARRAY_SIZE];

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  fftw_plan plan =
      fftw_plan_dft_1d(ARRAY_SIZE, signal, result, FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(plan);

  struct tensor vecsz;
  double *I = &result[0][0];
  double *O = &signal[0][0];
  struct problem_s *problem = fftw_mkproblem_rdft_0_d(&vecsz, I, O);
  fftw_destroy_plan(plan);
  fftw_destroy_problem(problem);

  return 0;
}