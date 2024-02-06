#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "double-conversion/double-conversion.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize StringToDoubleConverter
  int flags = double_conversion::StringToDoubleConverter::ALLOW_TRAILING_JUNK |
              double_conversion::StringToDoubleConverter::ALLOW_LEADING_SPACES |
              double_conversion::StringToDoubleConverter::ALLOW_TRAILING_SPACES |
              double_conversion::StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN;
  double_conversion::StringToDoubleConverter converter(flags, 0.0, 0.0, "inf", "nan");

  // Extract a string from the stream
  std::string str = stream.ConsumeBytesAsString(stream.remaining_bytes());
  int processed_characters_count;

  // Call the function to fuzz
  converter.StringToFloat(str.c_str(), str.size(), &processed_characters_count);

  return 0;
}