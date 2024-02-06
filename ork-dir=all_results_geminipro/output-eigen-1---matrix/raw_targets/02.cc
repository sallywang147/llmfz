#include <fuzzer/FuzzedDataProvider.h>

#include <Eigen/Dense>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int rows = stream.ConsumeIntegral<int>();
  const int cols = stream.ConsumeIntegral<int>();
  Eigen::Matrix<double, -1, -1, 0, -1, -1> matrix(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix(i, j) = stream.ConsumeFloatingPoint<double>();
    }
  }
  matrix.~Matrix();
  return 0;
}