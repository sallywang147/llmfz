#include <fuzzer/FuzzedDataProvider.h>
#include <Poco/RegularExpression.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  std::string regex_str = fuzzed_data.ConsumeRandomLengthString();
  std::string str_to_split = fuzzed_data.ConsumeRemainingBytesAsString();

  try {
    Poco::RegularExpression regex(regex_str);
    std::vector<std::string> result;
    regex.split(str_to_split, 0, result);
  } catch (Poco::RegularExpressionException&) {
    // We don't care about the exception, we just want to make sure the function doesn't crash.
  }

  return 0;
}