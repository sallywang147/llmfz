#include <fftw3.h>
#include <string>

extern "C" {
#include <fftw3.h>
}

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

  struct tensor vecsz;
  vecs.n = ARRAY_SIZE;
  vecs.dim = 1;
  vecs.type = FFTW_DOUBLE;

  struct problem_s *prob = fftw_mkproblem_rdft_0_d(&vecs, signal, result);

  fftw_plan plan = fftw_plan_dft_r2c(ARRAY_SIZE, signal, result, prob, FFTW_ESTIMATE);

  fftw_execute(plan);
  fftw_destroy_plan(plan);
  fftw_destroy_problem(prob);

  return 0;
}