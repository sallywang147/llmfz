#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include <Eigen/Dense>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t nrows = stream.ConsumeIntegral<size_t>();
  const size_t ncols = stream.ConsumeIntegral<size_t>();

  Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic> matrix;
  Eigen::Block<Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic>, Eigen::Dynamic, 1, true> block(matrix);
  Eigen::Transpose<Eigen::Block<Eigen::Matrix<std::complex<float>, Eigen::Dynamic, Eigen::Dynamic>, Eigen::Dynamic, 1, true>> transpose(block);

  transpose.resize(nrows, ncols);

  return 0;
}