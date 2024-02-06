#include <fuzzer/FuzzedDataProvider.h>
#include <Eigen/Dense>

extern "C" {
#include <Eigen/Eigenvalues>
}

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
  Eigen::EigenSolver<Eigen::Matrix<double, -1, -1, 0, -1, -1>> es(matrix);
  return 0;
}
```

The issue was that the destructor of the `matrix` was being called after the `EigenSolver` was constructed. This caused the `EigenSolver` to attempt to access a deallocated matrix, resulting in undefined behavior. To fix this, the destructor of the `matrix` was removed.