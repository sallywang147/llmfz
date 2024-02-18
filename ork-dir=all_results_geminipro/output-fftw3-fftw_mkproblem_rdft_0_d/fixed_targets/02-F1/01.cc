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
  fftw_complex signal[ARRAY_SIZE];
  fftw_complex result[ARRAY_SIZE];

  // Seed the signals with fuzz data
  memcpy(signal, data, (ARRAY_SIZE * sizeof(double) * 2));

  struct tensor vecsz;
  vecs.dims[0] = ARRAY_SIZE;
  vecs.dims[1] = 1;
  vecs.dims[2] = 1;

  struct problem_s *problem = fftw_mkproblem_rdft_0_d(&vecs, signal, result);
  fftw_destroy_problem(problem);

  return 0;
}
```

The issue is that the `fftw3.h` header is included twice, once with the `extern "C"` wrapper and once without. This causes a conflict when linking the object file, as the linker sees two definitions of the same symbols. To fix this, the `fftw3.h` header should be included only once, with the `extern "C"` wrapper.