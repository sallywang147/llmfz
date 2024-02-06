#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "fuzzer/FuzzedDataProvider.h"

#include "myanmar_tools/ZawgyiDetector/ZawgyiDetector.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  GMTZawgyiDetector *detector = GMTCreateZawgyiDetector();
  if (detector == nullptr) {
    return 0;
  }

  size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<char> input_utf8(input_length);
  stream.ConsumeBytes<char>(input_utf8.data(), input_length);

  double probability = GMTGetZawgyiProbabilityWithLength(detector, input_utf8.data(),
                                                      input_length);
  GMTDestroyZawgyiDetector(detector);
  return 0;
}