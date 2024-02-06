#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <double-conversion/double-conversion.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a StringToDoubleConverter with default parameters.
  double_conversion::StringToDoubleConverter converter(
      double_conversion::StringToDoubleConverter::NO_FLAGS,
      0.0, 0.0, "inf", "nan");

  // Consume the data as a string of characters.
  std::string str = stream.ConsumeRemainingBytesAsString();
  int processed_characters_count;

  // Call the function with the fuzzed data.
  converter.StringToFloat(str.c_str(), str.length(), &processed_characters_count);

  return 0;
}