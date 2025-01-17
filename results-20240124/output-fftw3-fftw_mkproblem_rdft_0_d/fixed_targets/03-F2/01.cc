#include <fftw3.h>
#include <cstdint>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  uint8_t ARRAY_SIZE = (*data) % 250 + 1;
  data++;
  size -= 1;
  if ((ARRAY_SIZE * sizeof(double)) > size) {
    return 0;
  }
  double signal[ARRAY_SIZE];

  // Seed the signals with fuzz data
  memcpy(signal, data, ARRAY_SIZE * sizeof(double));

  struct tensor vecsz = {ARRAY_SIZE, 1};
  fftw_mkproblem_rdft_0_d(&vecsz, signal, nullptr);

  return 0;
}