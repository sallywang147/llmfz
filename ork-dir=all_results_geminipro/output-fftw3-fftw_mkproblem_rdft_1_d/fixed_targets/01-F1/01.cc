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

  struct tensor sz;
  sz.dims = 1;
  sz.dim[0] = ARRAY_SIZE;

  struct tensor vecsz;
  vecsz.dims = 1;
  vecsz.dim[0] = ARRAY_SIZE;

  struct problem_s *problem = fftw_mkproblem_rdft_1_d(&sz, &vecsz, (double *)signal, (double *)result, FFTW_REAL_TO_HERM);

  fftw_plan plan = fftw_plan_dft_r2c(ARRAY_SIZE, signal, result, problem, FFTW_ESTIMATE);

  fftw_execute(plan);
  fftw_destroy_plan(plan);

  return 0;
}