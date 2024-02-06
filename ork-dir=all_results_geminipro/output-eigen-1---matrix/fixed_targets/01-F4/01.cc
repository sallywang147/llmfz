#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "Eigen/Core"

extern "C" {
#include "Eigen/Dense"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract matrix dimensions
  const int rows = stream.ConsumeIntegralInRange<int>(1, 100);
  const int cols = stream.ConsumeIntegralInRange<int>(1, 100);

  // Create a matrix
  Eigen::MatrixXd matrix(rows, cols);

  // Fill the matrix with random values
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix(i, j) = stream.ConsumeFloatingPoint<double>();
    }
  }

  // Destroy the matrix
  matrix.~MatrixXd();

  return 0;
}
```

The build issue is caused by the missing Eigen Dense header file. To fix it, we need to include the header file `Eigen/Dense` with `extern "C" {}` to ensure that the C++ compiler can find the necessary definitions.