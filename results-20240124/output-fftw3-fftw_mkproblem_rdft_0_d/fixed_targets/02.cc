#include <fftw3.h>
#include <string>

extern "C" {
#include <fftw3.h>
}

struct tensor {
  int dims;
  int dim[10];
};

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
  vecsz.dims = 1;
  vecsz.dim[0] = ARRAY_SIZE;

  // Call the function `fftw_mkproblem_rdft_0_d`
  struct problem_s *problem = fftw_mkproblem_rdft_0_d(&vecsz, (double *)signal, (double *)result);

  // Create a plan using the problem
  fftw_plan plan = fftw_plan_dft_r2c_1d(ARRAY_SIZE, (double *)signal, (fftw_complex *)result, FFTW_ESTIMATE);

  fftw_execute(plan);

  fftw_destroy_plan(plan);

  // Destroy the problem
  fftw_destroy_problem(problem);

  return 0;
}