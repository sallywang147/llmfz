#include <cstddef>
#include <cstdint>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Split the data into two parts for configuration and model files
  size_t dataSize = stream.remaining_bytes() / 2;
  
  std::string configuration = stream.ConsumeBytesAsString(dataSize);
  std::string model = stream.ConsumeRemainingBytesAsString();
  
  // Convert strings to char arrays
  char* configurationData = const_cast<char*>(configuration.c_str());
  char* modelData = const_cast<char*>(model.c_str());
  
  // Create pointers to char arrays
  char** configurationPtr = &configurationData;
  char** modelPtr = &modelData;
  
  // Initialize a network object
  cv::dnn::dnn4_v20231225::Net net;
  
  // Call the target function
  net = cv::dnn::dnn4_v20231225::detail::readNet(&net, configurationPtr, modelPtr);

  return 0;
}