#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "double-conversion.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  StringToDoubleConverter converter(StringToDoubleConverter::ALLOW_HEX | StringToDoubleConverter::ALLOW_OCTALS | StringToDoubleConverter::ALLOW_TRAILING_JUNK | StringToDoubleConverter::ALLOW_LEADING_SPACES | StringToDoubleConverter::ALLOW_TRAILING_SPACES | StringToDoubleConverter::ALLOW_SPACES_AFTER_SIGN | StringToDoubleConverter::ALLOW_CASE_INSENSIBILITY | StringToDoubleConverter::ALLOW_HEX_FLOATS,
                                    /*empty_string_value=*/0.0,
                                    /*junk_string_value=*/0.0, "inf", "nan");
  int num_digits_unused;
  std::vector<char> buffer(size);
  for (size_t i = 0; i < size; ++i) {
    buffer[i] = data[i];
  }
  converter.StringToFloat(buffer.data(), size, &num_digits_unused);
  return 0;
}