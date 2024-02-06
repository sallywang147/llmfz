#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

extern bool ada_can_parse_with_base(char * input, size_t input_length, char * base, size_t base_length);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string input = stream.ConsumeRandomLengthString();
  const std::string base = stream.ConsumeRemainingBytesAsString();

  ada_can_parse_with_base(const_cast<char*>(input.c_str()), input.size(), const_cast<char*>(base.c_str()), base.size());

  return 0;
}