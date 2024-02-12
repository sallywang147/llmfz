 #include <fftw3.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

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

  struct tensor vecsz;
  vecs.dims = 1;
  vecs.dim[0] = ARRAY_SIZE;

  struct problem_s * problem = fftw_mkproblem_rdft_0_d(&vecs, signal.data(), result.data());

  fftw_execute(problem);
  fftw_destroy_problem(problem);

  return 0;
}