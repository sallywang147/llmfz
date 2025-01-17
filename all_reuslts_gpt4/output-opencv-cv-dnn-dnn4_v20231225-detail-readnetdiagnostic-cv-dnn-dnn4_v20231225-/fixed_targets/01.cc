#include <cstddef>
#include <cstdint>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data to generate strings for configuration and model files
  size_t config_length = stream.ConsumeIntegralInRange<size_t>(0, size/2);
  std::string config = stream.ConsumeBytesAsString(config_length);
  std::string model = stream.ConsumeRemainingBytesAsString();

  // Create pointers for configuration and model files
  char* config_ptr = const_cast<char*>(config.c_str());
  char* model_ptr = const_cast<char*>(model.c_str());

  // Create pointers to pointers for configuration and model files
  char** config_pptr = &config_ptr;
  char** model_pptr = &model_ptr;

  // Declare a pointer to a cv::dnn::dnn4_v20231225::Net object
  cv::dnn::dnn4_v20231225::Net* net_ptr = nullptr;

  // Call the function to fuzz
  cv::dnn::dnn4_v20231225::detail::readNetDiagnostic(net_ptr, config_pptr, model_pptr);

  return 0;
}