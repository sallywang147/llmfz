#include <cstddef>
#include <cstdint>
#include <iosfwd>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/opencv.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  std::vector<uint8_t> model_data = fuzz_provider.ConsumeRemainingBytes();
  char *model_data_ptr = reinterpret_cast<char *>(model_data.data());

  std::vector<uint8_t> config_data = fuzz_provider.ConsumeRemainingBytes();
  char *config_data_ptr = reinterpret_cast<char *>(config_data.data());

  cv::dnn::Net* net = new cv::dnn::Net();
  cv::dnn::dnn4_v20231225::detail::readNet(net, &model_data_ptr, &config_data_ptr);
  delete net;

  return 0;
}