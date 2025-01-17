#include <fftw3.h>
#include <string>

extern "C" {
#include <fftw3/fftw3.h>
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

  struct fftw_tensor sz = {ARRAY_SIZE, 1, 1, 1, 1, 1, 1, 1};
  struct fftw_tensor vecsz = {ARRAY_SIZE, 1, 1, 1, 1, 1, 1, 1};

  // Call fftw_mkproblem_rdft_1_d to create a problem object
  struct fftw_problem *prob = fftw_mkproblem_rdft_1_d(&sz, &vecsz, (double *)signal, (double *)result, FFTW_REAL_TO_COMPLEX);

  // Create a plan using the problem object
  fftw_plan p = fftw_plan_dft_r2c(prob, (double *)signal, (fftw_complex *)result, FFTW_ESTIMATE);

  // Execute the plan
  fftw_execute(p);

  // Destroy the plan and problem object
  fftw_destroy_plan(p);
  fftw_destroy_problem(prob);

  return 0;
}