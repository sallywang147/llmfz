#include <cstddef>
#include <cstdint>
#include <iosfwd>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  std::string model_path = fuzz_provider.ConsumeBytesAsString(fuzz_provider.remaining_bytes()/2);
  std::string config_path = fuzz_provider.ConsumeRemainingBytesAsString();

  cv::dnn::dnn4_v20231225::Net net;
  cv::dnn::dnn4_v20231225::TFImporter importer;

  cv::dnn::dnn4_v20231225::(importer, &net, model_path.c_str(), config_path.c_str());

  return 0;
}