#include "astcenc_internal.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int quant_level = stream.ConsumeIntegralInRange<int>(1, 31);
  int character_count = stream.ConsumeIntegralInRange<int>(1, 32);
  int bit_offset = stream.ConsumeIntegralInRange<int>(0, 7);

  std::string input_data = stream.ConsumeBytesAsString(character_count);
  std::vector<char> output_data(character_count + 1, 0); // +1 for potential overflow

  encode_ise(quant_level, character_count, const_cast<char*>(input_data.c_str()), output_data.data(), bit_offset);

  return 0;
}