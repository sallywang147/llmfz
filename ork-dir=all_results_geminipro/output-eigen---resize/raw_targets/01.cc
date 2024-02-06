#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "Eigen/Core"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t nrows = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  const size_t ncols = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  Eigen::Transpose<Eigen::Block<Eigen::Matrix<std::__1::complex<float>, -1, -1, 0, -1, -1>, -1, 1, true>> transpose;
  transpose.resize(&transpose, nrows, ncols);
  return 0;
}