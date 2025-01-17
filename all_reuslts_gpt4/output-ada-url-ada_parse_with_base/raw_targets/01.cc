#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" char * ada_parse_with_base(char * input, size_t input_length, char * base, size_t base_length);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  const size_t input_length = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  std::string input = provider.ConsumeBytesAsString(input_length);

  const size_t base_length = provider.remaining_bytes();
  std::string base = provider.ConsumeRemainingBytesAsString();

  ada_parse_with_base(const_cast<char*>(input.c_str()), input_length, const_cast<char*>(base.c_str()), base_length);

  return 0;
}