#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

#include "guetzli/processor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  guetzli::Params params;
  params.butteraugli_target = stream.ConsumeFloatingPoint<double>();
  params.hf_asymmetry = stream.ConsumeFloatingPoint<double>();
  params.butteraugli_target = stream.ConsumeFloatingPoint<double>();

  guetzli::ProcessStats stats;

  const size_t width = stream.ConsumeIntegralInRange<size_t>(1, 4096);
  const size_t height = stream.ConsumeIntegralInRange<size_t>(1, 4096);
  const size_t num_pixels = width * height;
  if (num_pixels == 0) {
    return 0;
  }

  std::vector<uint8_t> rgb_data = stream.ConsumeBytes<uint8_t>(num_pixels * 3);
  if (rgb_data.size() != num_pixels * 3) {
    return 0;
  }

  std::string output;

  guetzli::Process(&params, &stats, &rgb_data, width, height, &output);

  return 0;
}