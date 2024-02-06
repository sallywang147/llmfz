#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "double-conversion/double-conversion.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define the parameters for the StringToFloat function
  const double_conversion::StringToDoubleConverter::Flags flags =
      double_conversion::StringToDoubleConverter::ALLOW_TRAILING_JUNK |
      double_conversion::StringToDoubleConverter::ALLOW_LEADING_SPACES |
      double_conversion::StringToDoubleConverter::ALLOW_TRAILING_SPACES |
      double_conversion::StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN;

  const double_conversion::StringToDoubleConverter converter(
      flags, 0.0, 0.0, "inf", "nan");

  // Consume data to create a buffer of shorts
  size_t buffer_length = stream.remaining_bytes() / sizeof(short);
  std::vector<short> buffer(buffer_length);
  stream.ConsumeData(buffer.data(), buffer_length * sizeof(short));

  // Initialize processed_characters_count
  int processed_characters_count = 0;

  // Call the function to fuzz
  converter.StringToFloat(buffer.data(), buffer_length, &processed_characters_count);

  return 0;
}