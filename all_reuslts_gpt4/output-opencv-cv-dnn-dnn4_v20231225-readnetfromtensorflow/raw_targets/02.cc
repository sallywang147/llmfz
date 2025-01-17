#include <cstddef>
#include <cstdint>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  std::vector<uint8_t> buffer1 = fuzz_provider.ConsumeBytes<uint8_t>(fuzz_provider.remaining_bytes() / 2);
  std::vector<uint8_t> buffer2 = fuzz_provider.ConsumeRemainingBytes<uint8_t>();

  cv::dnn::dnn4_v20231225::Net net;

  try {
    cv::dnn::dnn4_v20231225::readNetFromTensorflow(&net, &buffer1, &buffer2);
  } catch (cv::Exception& e) {
    // Ignore exceptions thrown by OpenCV
  }

  return 0;
}