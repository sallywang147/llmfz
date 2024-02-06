#include <fuzzer/FuzzedDataProvider.h>
#include <double-conversion/double-conversion.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Create a StringToDoubleConverter object
  int flags = double_conversion::StringToDoubleConverter::ALLOW_LEADING_SPACES |
              double_conversion::StringToDoubleConverter::ALLOW_TRAILING_SPACES;
  double_conversion::StringToDoubleConverter converter(flags, 0.0, 0.0, "inf", "nan");

  // Get a string from the data provider
  std::string str = provider.ConsumeRemainingBytesAsString();
  int processed_characters_count = 0;

  // Call the target function
  float result = converter.StringToFloat(str.c_str(), str.length(), &processed_characters_count);

  return 0;
}