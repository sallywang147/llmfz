#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "double-conversion.h"

using double_conversion::StringToDoubleConverter;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }
  // Convert the input to a short array.
  std::vector<short> buffer(size);
  for (size_t i = 0; i < size; ++i) {
    buffer[i] = static_cast<short>(data[i]);
  }
  // Create a StringToDoubleConverter object.
  StringToDoubleConverter converter(
      StringToDoubleConverter::ALLOW_HEX |
          StringToDoubleConverter::ALLOW_OCTALS |
          StringToDoubleConverter::ALLOW_TRAILING_JUNK |
          StringToDoubleConverter::ALLOW_LEADING_SPACES |
          StringToDoubleConverter::ALLOW_TRAILING_SPACES |
          StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN |
          StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY |
          StringToDoubleConverter::ALLOW_HEX_FLOATS,
      /*empty_string_value=*/0.0,
      /*junk_string_value=*/0.0, "inf", "nan");
  // Convert the short array to a double.
  int processed_characters_count;
  double result = converter.StringTo<double>(&buffer[0], buffer.size(),
                                           &processed_characters_count);
  // Use the result.
  (void)result;
  return 0;
}