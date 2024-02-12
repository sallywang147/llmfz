#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstring>

extern "C" {
#include "encode_ise.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int quant_level = stream.ConsumeIntegral<int>();
  const int character_count = stream.ConsumeIntegral<int>();
  const char* input_data = reinterpret_cast<const char*>(stream.ConsumeBytes<uint8_t>(character_count).data());
  char* output_data = new char[character_count];
  const int bit_offset = stream.ConsumeIntegral<int>();

  encode_ise(quant_level, character_count, input_data, output_data, bit_offset);

  delete[] output_data;

  return 0;
}