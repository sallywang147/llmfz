#include "fuzzer/FuzzedDataProvider.h"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
#include "encode_ise.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  int quant_level = provider.ConsumeIntegralInRange<int>(0, 100);
  int character_count = provider.ConsumeIntegralInRange<int>(0, 1000);
  std::vector<char> input_data(character_count);
  provider.ConsumeBytes(input_data.data(), input_data.size());
  std::vector<char> output_data(character_count);
  int bit_offset = provider.ConsumeIntegralInRange<int>(0, 1000);
  encode_ise(quant_level, character_count, input_data.data(), output_data.data(), bit_offset);
  return 0;
}