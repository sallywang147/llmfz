#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "ada_set_href.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const std::string input = stream.ConsumeBytesAsString(input_length);
  const size_t output_length = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* output = static_cast<char*>(std::malloc(output_length));
  bool ret = ada_set_href(output, const_cast<char*>(input.c_str()), input_length);
  std::free(output);
  return ret;
}