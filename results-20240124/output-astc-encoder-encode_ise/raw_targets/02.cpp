 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int quant_level = stream.ConsumeIntegral<int>();
  const int character_count = stream.ConsumeIntegral<int>();
  const int bit_offset = stream.ConsumeIntegral<int>();

  std::vector<char> input_data = stream.ConsumeBytes<char>(character_count);
  std::vector<char> output_data(character_count);

  encode_ise(quant_level, character_count, input_data.data(), output_data.data(),
             bit_offset);

  return 0;
}