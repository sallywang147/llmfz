#include <cstddef>
#include <cstdint>
#include <iosfwd>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/opencv.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  std::vector<uint8_t> model_bytes = fuzz_provider.ConsumeRemainingBytes();
  char *model_data = reinterpret_cast<char *>(model_bytes.data());

  std::vector<uint8_t> config_bytes = fuzz_provider.ConsumeRemainingBytes();
  char *config_data = reinterpret_cast<char *>(config_bytes.data());

  cv::dnn::dnn4_v20231225::Net net;
  cv::dnn::dnn4_v20231225::(cv::dnn::dnn4_v20231225::(anonymous namespace)::TFImporter)::ImportFromTF(nullptr, &net, model_data, config_data);

  return 0;
}