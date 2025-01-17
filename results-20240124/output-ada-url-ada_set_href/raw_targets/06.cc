 #include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  const std::string input_string = stream.ConsumeRandomLengthString(input_length);
  const size_t result_length = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  char result[result_length];
  if (!ada_set_href(result, const_cast<char*>(input_string.c_str()), input_length)) {
    return 0;
  }
  return 0;
}