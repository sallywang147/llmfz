#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" char * ada_parse_with_base(char * input, size_t input_length, char * base, size_t base_length);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Split the data into two parts: one for 'input' and one for 'base'.
  const size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, size - 1);
  std::string input = stream.ConsumeBytesAsString(input_length);
  std::string base = stream.ConsumeRemainingBytesAsString();

  ada_parse_with_base(const_cast<char*>(input.c_str()), input.size(), const_cast<char*>(base.c_str()), base.size());

  return 0;
}