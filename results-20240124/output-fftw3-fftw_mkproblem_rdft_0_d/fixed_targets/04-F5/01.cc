#include <fftw3.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

extern "C" {
#include <fftw3.h>
struct tensor {
  int n, m, k;
};
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  uint8_t ARRAY_SIZE = (*data) % 250 + 1;
  data++;
  size -= 1;
  if ((ARRAY_SIZE * sizeof(double) * 2) > size) {
    return 0;
  }
  double signal[ARRAY_SIZE];
  double result[ARRAY_SIZE];
  double *I = signal;
  double *O = result;

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  struct tensor vecsz = {ARRAY_SIZE, 1, 1};

  fftw_plan problem = fftw_plan_dft_r2c_1d(ARRAY_SIZE, signal, (fftw_complex *)result, FFTW_ESTIMATE);
  fftw_execute(problem);
  fftw_destroy_plan(problem);

  // Call the function `fftw_mkproblem_rdft_0_d`
  fftw_mkproblem_rdft_0_d(&vecsz, I, O);

  return 0;
}