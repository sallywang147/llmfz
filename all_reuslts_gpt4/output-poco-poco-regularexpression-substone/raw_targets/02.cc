#include <fuzzer/FuzzedDataProvider.h>
#include <Poco/RegularExpression.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  std::string pattern = fuzzed_data.ConsumeRandomLengthString();
  std::string input = fuzzed_data.ConsumeRandomLengthString();
  std::string replacement = fuzzed_data.ConsumeRemainingBytesAsString();

  try {
    Poco::RegularExpression regex(pattern);
    size_t offset = fuzzed_data.ConsumeIntegralInRange<size_t>(0, input.size());
    int options = fuzzed_data.ConsumeIntegral<int>();
    regex.subst(input, replacement, options, offset);
  } catch (...) {
    // Ignore exceptions.
  }

  return 0;
}