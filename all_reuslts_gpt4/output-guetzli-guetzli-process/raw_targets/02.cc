#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "guetzli/processor.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  guetzli::Params params;
  params.butteraugli_target = stream.ConsumeFloatingPoint<double>();
  params.hf_asymmetry = stream.ConsumeFloatingPoint<double>();

  guetzli::ProcessStats stats;

  std::vector<uint8_t> input_data = stream.ConsumeRemainingBytes<uint8_t>();

  int width = stream.ConsumeIntegral<int>();
  int height = stream.ConsumeIntegral<int>();

  std::string output_data;

  guetzli::Process(&params, &stats, &input_data, width, height, &output_data);

  return 0;
}