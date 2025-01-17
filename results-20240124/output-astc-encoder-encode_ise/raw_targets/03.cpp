 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int quant_level = stream.ConsumeIntegral<int>();
  const int character_count = stream.ConsumeIntegral<int>();
  const std::string input_data = stream.ConsumeRemainingBytesAsString();
  const std::string output_data = stream.ConsumeRemainingBytesAsString();
  const int bit_offset = stream.ConsumeIntegral<int>();

  encode_ise(quant_level, character_count,
             const_cast<char*>(input_data.c_str()),
             const_cast<char*>(output_data.c_str()), bit_offset);
  return 0;
}