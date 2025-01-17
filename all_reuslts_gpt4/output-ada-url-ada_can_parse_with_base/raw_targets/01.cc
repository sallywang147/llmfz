#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  if (stream.remaining_bytes() < 2) {
    return 0;
  }

  size_t input_length = stream.ConsumeIntegralInRange<size_t>(1, stream.remaining_bytes() / 2);
  std::string input = stream.ConsumeBytesAsString(input_length);
  std::string base = stream.ConsumeRemainingBytesAsString();

  ada_can_parse_with_base(const_cast<char*>(input.c_str()), input_length, const_cast<char*>(base.c_str()), base.size());

  return 0;
}