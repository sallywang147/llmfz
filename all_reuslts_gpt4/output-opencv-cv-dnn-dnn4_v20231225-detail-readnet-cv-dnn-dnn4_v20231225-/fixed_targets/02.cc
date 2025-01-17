#include <cstddef>
#include <cstdint>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Split the data into two parts to simulate two file paths
  std::string data1 = fuzzed_data.ConsumeBytesAsString(fuzzed_data.remaining_bytes() / 2);
  std::string data2 = fuzzed_data.ConsumeRemainingBytesAsString();

  // Convert the strings into char pointers
  char *configFile = const_cast<char*>(data1.c_str());
  char *modelFile = const_cast<char*>(data2.c_str());

  // Create a pointer to a Net object
  cv::dnn::dnn4_v20231225::Net* net = new cv::dnn::dnn4_v20231225::Net();

  // Call the function
  try {
    *net = cv::dnn::dnn4_v20231225::detail::readNet(net, &configFile, &modelFile);
  } catch (...) {
    // Ignore all exceptions
  }

  // Cleanup
  delete net;

  return 0;
}