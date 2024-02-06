#include <cstddef>
#include <cstdint>
#include <iosfwd>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/dnn/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  std::string model = fuzz_provider.ConsumeBytesAsString(fuzz_provider.ConsumeIntegralInRange(0, size));
  std::string config = fuzz_provider.ConsumeRemainingBytesAsString();

  char* model_ptr = const_cast<char*>(model.c_str());
  char* config_ptr = const_cast<char*>(config.c_str());

  cv::dnn::dnn4_v20231225::Net net;
  cv::dnn::dnn4_v20231225::detail::readNetDiagnostic(&net, &model_ptr, &config_ptr);

  return 0;
}