#include <cstddef>
#include <cstdint>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  cv::dnn::dnn4_v20231225::Net net;

  // Consume half of the input for the first vector and the rest for the second vector
  size_t half_size = size / 2;
  std::vector<uint8_t> buffer1 = fuzz_provider.ConsumeBytes<uint8_t>(half_size);
  std::vector<uint8_t> buffer2 = fuzz_provider.ConsumeRemainingBytes<uint8_t>();

  try {
    cv::dnn::dnn4_v20231225::readNetFromTensorflow(&net, &buffer1, &buffer2);
  } catch (...) {
    // Ignore all exceptions
  }

  return 0;
}