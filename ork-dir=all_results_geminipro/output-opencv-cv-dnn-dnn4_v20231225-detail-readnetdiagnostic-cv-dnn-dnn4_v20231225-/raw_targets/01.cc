#include <cstddef>
#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include <opencv2/dnn.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzz_provider(data, size);

  std::vector<uint8_t> net_data = fuzz_provider.ConsumeRemainingBytes();
  cv::dnn::Net net;
  cv::dnn::dnn4_v20231225::detail::readNetDiagnostic(
      &net, reinterpret_cast<char **>(&net_data[0]),
      reinterpret_cast<char **>(&net_data[0] + net_data.size()));
  return 0;
}