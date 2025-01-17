 #include <fftw3.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // For reference, fftw_compelx is defined:
  // typedef double fftw_complex[2]
  fftw_complex *signal = nullptr;
  fftw_complex *result = nullptr;
  fftw_plan plan = nullptr;
  struct problem_s *problem = nullptr;
  struct tensor *sz = nullptr;
  struct tensor *vecsz = nullptr;
  double *I = nullptr;
  double *O = nullptr;
  int kind = 0;
  if (size < 1) {
    return 0;
  }
  uint8_t ARRAY_SIZE = (*data) % 250 + 1;
  data++;
  size -= 1;
  if ((ARRAY_SIZE * sizeof(double) * 2) > size) {
    return 0;
  }
  signal = (fftw_complex *)malloc(ARRAY_SIZE * sizeof(double) * 2);
  result = (fftw_complex *)malloc(ARRAY_SIZE * sizeof(double) * 2);
  sz = (struct tensor *)malloc(sizeof(struct tensor));
  vecsz = (struct tensor *)malloc(sizeof(struct tensor));
  I = (double *)malloc(ARRAY_SIZE * sizeof(double) * 2);
  O = (double *)malloc(ARRAY_SIZE * sizeof(double) * 2);

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  sz->dims = 1;
  sz->size = ARRAY_SIZE;
  vecsz->dims = 1;
  vecsz->size = ARRAY_SIZE;

  problem = fftw_mkproblem_rdft_1_d(sz, vecsz, I, O, kind);
  fftw_execute(problem);

  free(signal);
  free(result);
  free(sz);
  free(vecsz);
  free(I);
  free(O);

  return 0;
}