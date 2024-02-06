#include <cstddef>
#include <cstdint>
#include <iosfwd>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/opencv.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  cv::dnn::dnn4_v20231225::Net* fuzz_net = new cv::dnn::dnn4_v20231225::Net();

  char** fuzz_model_path = new char*[1];
  fuzz_model_path[0] = fuzz_provider.ConsumeRemainingBytesAsString().c_str();

  char** fuzz_config_path = new char*[1];
  fuzz_config_path[0] = fuzz_provider.ConsumeRemainingBytesAsString().c_str();

  cv::dnn::dnn4_v20231225::detail::readNetDiagnostic<cv::dnn::dnn4_v20231225::(cv::dnn::dnn4_v20231225::Net*, char**, char**)>(fuzz_net, fuzz_model_path, fuzz_config_path);

  delete fuzz_net;
  delete[] fuzz_model_path;
  delete[] fuzz_config_path;

  return 0;
}