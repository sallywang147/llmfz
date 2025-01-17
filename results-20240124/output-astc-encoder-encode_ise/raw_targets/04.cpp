 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int quant_level = stream.ConsumeIntegralInRange<int>(0, 100);
  const int character_count = stream.ConsumeIntegralInRange<int>(1, 100);
  char* input_data = new char[character_count];
  stream.ConsumeData(input_data, character_count);
  char* output_data = new char[character_count];
  const int bit_offset = stream.ConsumeIntegralInRange<int>(0, 100);

  encode_ise(quant_level, character_count, input_data, output_data, bit_offset);

  delete[] input_data;
  delete[] output_data;

  return 0;
}