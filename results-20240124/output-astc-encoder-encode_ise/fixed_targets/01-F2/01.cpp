#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "astc_codec_internals.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int quant_level = stream.ConsumeIntegral<int>();
  const int character_count = stream.ConsumeIntegral<int>();
  char input_data[character_count];
  stream.ReadData(input_data, character_count);
  char output_data[character_count];
  const int bit_offset = stream.ConsumeIntegral<int>();
  encode_ise(quant_level, character_count, input_data, output_data, bit_offset);
  return 0;
}