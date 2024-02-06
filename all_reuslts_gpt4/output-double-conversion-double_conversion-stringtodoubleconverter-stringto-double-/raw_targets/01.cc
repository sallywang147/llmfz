#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "double-conversion/double-conversion.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the converter
  double_conversion::StringToDoubleConverter converter(
    double_conversion::StringToDoubleConverter::ALLOW_TRAILING_JUNK |
    double_conversion::StringToDoubleConverter::ALLOW_LEADING_SPACES,
    0.0, 0.0, "inf", "nan");

  // Extract a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  int processed_characters_count = 0;

  // Call the function to fuzz
  double result = converter.StringToDouble(str.c_str(), str.length(), &processed_characters_count);

  return 0;
}