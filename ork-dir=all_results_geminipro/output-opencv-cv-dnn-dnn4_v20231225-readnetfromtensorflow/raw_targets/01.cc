#include <cstdint>
#include <cstddef>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  std::vector<uint8_t> model_data = fuzz_provider.ConsumeRemainingBytes();
  std::vector<uint8_t> config_data = fuzz_provider.ConsumeRemainingBytes();

  cv::dnn::Net net;
  cv::dnn::dnn4_v20231225::readNetFromTensorflow(&net, model_data, config_data);

  return 0;
}