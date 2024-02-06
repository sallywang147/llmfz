#include <cstddef>
#include <cstdint>
#include <iosfwd>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  // Consume half of the data for config file and the rest for model file
  std::string config_file = fuzz_provider.ConsumeBytesAsString(size / 2);
  std::string model_file = fuzz_provider.ConsumeRemainingBytesAsString();

  // Create TFImporter and Net objects
  cv::dnn::dnn4_v20231225::Net net;
  cv::dnn::dnn4_v20231225::TFImporter importer;

  // Call the target function
  cv::dnn::dnn4_v20231225::(importer, &net, config_file.c_str(), model_file.c_str());

  return 0;
}