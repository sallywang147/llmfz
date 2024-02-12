 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "ada.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_length = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  const std::string input = stream.ConsumeRandomLengthString(max_length);
  ada_can_parse(const_cast<char*>(input.c_str()), input.size());
  return 0;
}