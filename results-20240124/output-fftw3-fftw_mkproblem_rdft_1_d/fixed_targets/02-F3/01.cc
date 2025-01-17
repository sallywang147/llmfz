#include <fftw3.h>
#include <string>

extern "C" {
#include <fftw3.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // For reference, fftw_compelx is defined:
  // typedef double fftw_complex[2]
  fftw_complex *signal = nullptr;
  fftw_complex *result = nullptr;
  fftw_plan plan = nullptr;
  fftw_iodim dims[1];
  fftw_iodim howmany_dims[1];
  fftw_iodim istride[1];
  fftw_iodim ostride[1];
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
  I = (double *)malloc(ARRAY_SIZE * sizeof(double) * 2);
  O = (double *)malloc(ARRAY_SIZE * sizeof(double) * 2);

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  dims[0] = ARRAY_SIZE;
  howmany_dims[0] = 1;
  istride[0] = 1;
  ostride[0] = 1;

  plan = fftw_plan_guru_dft_r2c(1, dims, howmany_dims, istride, ostride, I, O, FFTW_ESTIMATE);
  fftw_execute(plan);

  // Call the missing function
  fftw_rdft_1d(ARRAY_SIZE, I, O, kind);

  free(signal);
  free(result);
  free(I);
  free(O);
  fftw_destroy_plan(plan);

  return 0;
}