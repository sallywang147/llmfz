#include <fftw3.h>
#include <string>

extern "C" {
#include <fftw3-mpi.h>
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
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

  // Create a problem
  fftw_plan problem =
      fftw_plan_dft_r2c_1d(ARRAY_SIZE, (double *)signal, (fftw_complex *)result, FFTW_ESTIMATE);

  // Execute the problem
  fftw_execute(problem);

  // Destroy the problem
  fftw_destroy_plan(problem);

  return 0;
}
}