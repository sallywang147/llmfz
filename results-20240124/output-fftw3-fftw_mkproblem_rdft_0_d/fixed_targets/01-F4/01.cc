#include <fftw3.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

extern "C" {
#include <fftw3.h>
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
  std::vector<double> signal(ARRAY_SIZE);
  std::vector<double> result(ARRAY_SIZE);

  // Seed the signals with fuzz data
  memcpy(signal.data(), data, (ARRAY_SIZE * sizeof(double) * 2));

  fftw_iodim vecs;
  vecs.n = 1;
  vecs.is = ARRAY_SIZE;

  // Fix the function name to 'fftw_plan_dft_r2c_1d'
  fftw_plan problem = fftw_plan_dft_r2c_1d(vecs.n, signal.data(),
                                                (fftw_complex *)result.data(),
                                                FFTW_ESTIMATE);

  fftw_execute(problem);
  fftw_destroy_plan(problem);

  // Add the call to fftw_mkproblem_rdft_0_d
  fftw_mkproblem_rdft_0_d(&vecs, signal.data(), result.data());

  return 0;
}