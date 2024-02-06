#include <fuzzer/FuzzedDataProvider.h>
#include <Eigen/Dense>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Consume data for rows and cols of the matrix. Limit the size to prevent excessive memory usage.
    int rows = stream.ConsumeIntegralInRange<int>(1, 100);
    int cols = stream.ConsumeIntegralInRange<int>(1, 100);

    // Create a dynamic Eigen Matrix
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> matrix(rows, cols);

    // Fill the matrix with data from the fuzzer
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (stream.remaining_bytes() < sizeof(double)) {
                goto EXIT;
            }
            matrix(i, j) = stream.ConsumeFloatingPoint<double>();
        }
    }

EXIT:
    // Call the destructor explicitly
    matrix.~Matrix();

    return 0;
}