#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::string input = provider.ConsumeRandomLengthString(input_size);

  struct GMTZawgyiDetector detector;
  GMTInitZawgyiDetector(&detector);
  double probability = GMTGetZawgyiProbability(&detector, const_cast<char*>(input.c_str()));
  GMTDestroyZawgyiDetector(&detector);

  return 0;
}