#include <fftw3.h>
#include <string>

// Include the necessary header file to use the 'tensor' struct.
#include <fftw3-mpi.h>

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

  // Define the dimensions of the signal and vector.
  tensor sz;
  sz.dims = 1;
  sz.dim[0] = ARRAY_SIZE;
  tensor vecsz;
  vecsz.dims = 1;
  vecsz.dim[0] = ARRAY_SIZE;

  // Perform the 1D real-to-complex discrete Fourier transform.
  fftw_mkproblem_rdft_1_d(&sz, &vecsz, (double *)signal, (double *)result,
                          FFTW_REDFT10);

  return 0;
}