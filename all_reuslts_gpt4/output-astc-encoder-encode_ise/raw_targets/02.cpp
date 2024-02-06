#include <fuzzer/FuzzedDataProvider.h>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);
  
  // Extract the quant_level and character_count from the data stream
  int quant_level = stream.ConsumeIntegralInRange<int>(0, 255);
  int character_count = stream.ConsumeIntegralInRange<int>(0, 255);
  
  // Check if we have enough data left for the input_data array
  if (stream.remaining_bytes() < character_count) {
    return 0;
  }
  
  // Extract the input_data array from the data stream
  std::vector<char> input_data = stream.ConsumeBytes<char>(character_count);
  
  // Check if we have enough data left for the output_data array
  if (stream.remaining_bytes() < character_count) {
    return 0;
  }
  
  // Extract the output_data array from the data stream
  std::vector<char> output_data = stream.ConsumeBytes<char>(character_count);
  
  // Extract the bit_offset from the data stream
  int bit_offset = stream.ConsumeIntegral<int>();
  
  // Call the function under test
  encode_ise(quant_level, character_count, input_data.data(), output_data.data(), bit_offset);
  
  return 0;
}