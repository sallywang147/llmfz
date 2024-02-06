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
  fftw_complex *signal = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * ARRAY_SIZE);
  fftw_complex *result = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * ARRAY_SIZE);

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  struct tensor sz, vecs;
  sz.dims = 1;
  sz.dim[0] = ARRAY_SIZE;
  vecs.dims = 1;
  vecs.dim[0] = ARRAY_SIZE;

  fftw_mkproblem_rdft_1_d(&sz, &vecs, signal, result, FFTW_REAL_TO_COMPLEX);

  fftw_free(signal);
  fftw_free(result);

  return 0;
}