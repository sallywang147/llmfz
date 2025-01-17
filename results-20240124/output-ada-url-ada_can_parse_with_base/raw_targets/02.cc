 #include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, size);
  const size_t base_length = stream.ConsumeIntegralInRange<size_t>(0, size);
  const std::string input = stream.ConsumeBytesAsString(input_length);
  const std::string base = stream.ConsumeBytesAsString(base_length);

  bool result = ada_can_parse_with_base(const_cast<char*>(input.c_str()),
                                         input_length, const_cast<char*>(base.c_str()),
                                         base_length);
  return 0;
}