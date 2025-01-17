 #include <fftw3.h>
#include <string>

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
  fftw_complex signal[ARRAY_SIZE];
  fftw_complex result[ARRAY_SIZE];

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  struct tensor vecsz;
  vecs.ndims = 1;
  vecs.dims[0] = ARRAY_SIZE;
  struct problem_s *problem = fftw_mkproblem_rdft_0_d(&vecs, (double*)signal, (double*)result);

  fftw_destroy_problem(problem);

  return 0;
}