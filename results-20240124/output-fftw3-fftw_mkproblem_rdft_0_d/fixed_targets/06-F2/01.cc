#include <fftw3.h>
#include <string>

extern "C" {
#include <fftw3/fftw3.h>
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

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  struct problem_s *problem = fftw_mkproblem_rdft_0_d(NULL, signal, result);
  fftw_destroy_plan(problem);

  return 0;
}