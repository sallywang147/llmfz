#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/opencv.hpp>

extern "C" {
#include <opencv2/dnn.hpp>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::vector<uint8_t> model_bytes = provider.ConsumeRemainingBytes();
  cv::dnn::Net net;
  std::vector<std::string> layers_names;
  std::vector<cv::Mat> layers_weights;

  cv::dnn::dnn4_v20231225::readNetFromTensorflow(
      &net, &layers_names, &layers_weights, model_bytes.data(), model_bytes.size());

  return 0;
}