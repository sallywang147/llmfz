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
  struct tensor sz, vecsz;
  sz.dims[0] = ARRAY_SIZE;
  vecs.dims[0] = ARRAY_SIZE;
  fftw_plan problem =
      fftw_mkproblem_rdft_1_d(&sz, &vecs, (double *)signal, (double *)result, FFTW_FORWARD);

  // Execute the problem
  fftw_execute(problem);

  // Destroy the problem
  fftw_destroy_plan(problem);

  return 0;
}
}