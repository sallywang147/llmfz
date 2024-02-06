#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Select a quantization level
  int quant_level = provider.ConsumeIntegralInRange<int>(0, 15);

  // Select a character count
  int character_count = provider.ConsumeIntegralInRange<int>(0, 1024);

  // Generate input data
  std::vector<char> input_data(character_count);
  provider.ConsumeBytes(input_data.data(), input_data.size());

  // Generate output data
  std::vector<char> output_data(character_count);

  // Select a bit offset
  int bit_offset = provider.ConsumeIntegralInRange<int>(0, 7);

  // Call the function under test
  encode_ise(quant_level, character_count, input_data.data(), output_data.data(), bit_offset);

  return 0;
}