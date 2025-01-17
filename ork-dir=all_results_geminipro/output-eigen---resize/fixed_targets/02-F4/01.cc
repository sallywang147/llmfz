#include "Eigen/Core"
#include "Eigen/Eigenvalues"

#include <fuzzer/FuzzedDataProvider.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t nrows = stream.ConsumeIntegral<size_t>();
  const size_t ncols = stream.ConsumeIntegral<size_t>();

  Eigen::Matrix<std::complex<float>, -1, -1, Eigen::RowMajor> matrix(nrows, ncols);
  for (size_t i = 0; i < nrows; ++i) {
    for (size_t j = 0; j < ncols; ++j) {
      matrix(i, j) = std::complex<float>(stream.ConsumeFloatingPoint<float>(),
                                          stream.ConsumeFloatingPoint<float>());
    }
  }

  Eigen::Transpose<Eigen::Block<Eigen::Matrix<std::complex<float>, -1, -1, 0, -1, -1>, -1, 1, true>> transpose(matrix.block(0, 0, nrows, 1));
  transpose.resize(transpose, ncols, nrows);

  return 0;
}