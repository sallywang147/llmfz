#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the size of the tensor.
  struct tensor sz;
  sz.dim = stream.ConsumeIntegralInRange<uint8_t>(0, 10); // Assuming tensor dimension in reasonable range.
  sz.n = stream.ConsumeIntegral<uint32_t>();
  sz.os = stream.ConsumeIntegral<uint32_t>();
  sz.is = stream.ConsumeIntegral<uint32_t>();

  // Define the size of the vector tensor.
  struct tensor vecsz;
  vecsz.dim = stream.ConsumeIntegralInRange<uint8_t>(0, 10); // Assuming tensor dimension in reasonable range.
  vecsz.n = stream.ConsumeIntegral<uint32_t>();
  vecsz.os = stream.ConsumeIntegral<uint32_t>();
  vecsz.is = stream.ConsumeIntegral<uint32_t>();

  // Define the input and output arrays.
  std::vector<double> I = stream.ConsumeBytes<double>(stream.ConsumeIntegralInRange(0, 100)); // Assuming reasonable size.
  std::vector<double> O = stream.ConsumeBytes<double>(stream.ConsumeIntegralInRange(0, 100)); // Assuming reasonable size.

  // Define the kind of transform.
  int kind = stream.ConsumeIntegral<int>();

  // Call the function.
  struct problem_s* problem = fftw_mkproblem_rdft_1_d(&sz, &vecsz, I.data(), O.data(), kind);

  // Clean up.
  fftw_problem_destroy(problem);

  return 0;
}