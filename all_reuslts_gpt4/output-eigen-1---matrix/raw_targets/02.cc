#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <Eigen/Dense>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_size = 100;
  
  // Consume data for rows and columns
  int rows = stream.ConsumeIntegralInRange<int>(0, max_size);
  int cols = stream.ConsumeIntegralInRange<int>(0, max_size);
  
  // Create Matrix object
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix(rows, cols);
  
  // Fill the matrix with data
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (stream.remaining_bytes() < sizeof(double)) {
        // Not enough data to consume
        return 0;
      }
      matrix(i, j) = stream.ConsumeFloatingPoint<double>();
    }
  }

  // Call the destructor explicitly
  matrix.~Matrix();

  return 0;
}