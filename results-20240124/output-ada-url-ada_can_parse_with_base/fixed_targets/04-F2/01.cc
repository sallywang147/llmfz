#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t input_length = stream.ConsumeIntegralInRange<size_t>(0, 100);
  const size_t base_length = stream.ConsumeIntegralInRange<size_t>(0, 100);
  auto input = stream.ConsumeBytes<char>(input_length);
  auto base = stream.ConsumeBytes<char>(base_length);

  // Include the necessary header file for the missing function.
  #include "ada_parser.h"

  ada_can_parse_with_base(input.data(), input_length, base.data(), base_length);

  return 0;
}