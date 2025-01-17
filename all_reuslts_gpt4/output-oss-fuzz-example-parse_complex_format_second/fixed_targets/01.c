#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <string>

#include "complex_parser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  parse_complex_format_second(str.c_str());
  return 0;
}