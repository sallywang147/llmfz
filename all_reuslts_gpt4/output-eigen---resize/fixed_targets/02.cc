#include <fuzzer/FuzzedDataProvider.h>
#include <Eigen/Dense>

#include <cstddef>
#include <cstdint>
#include <complex>

using Eigen::Matrix;
using Eigen::Block;
using Eigen::Transpose;
using std::complex;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t nrows = stream.ConsumeIntegral<size_t>();
  size_t ncols = stream.ConsumeIntegral<size_t>();

  // Initialize a dynamic-size Eigen matrix with complex<float> elements
  Matrix<complex<float>, -1, -1, 0, -1, -1> mat(nrows, ncols);

  // Create a block view into the matrix
  Block<Matrix<complex<float>, -1, -1, 0, -1, -1>, -1, 1, true> block(mat);

  // Transpose the block
  Transpose<Block<Matrix<complex<float>, -1, -1, 0, -1, -1>, -1, 1, true>> transposed(block);

  // Resize the transposed block
  transposed.resize(nrows, ncols);

  return 0;
}