#include <fuzzer/FuzzedDataProvider.h>
#include <vector>
#include <string>

#include "Poco/RegularExpression.h"

extern "C" {
#include <cstdint>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  std::string regex_string = stream.ConsumeRemainingBytesAsString();
  Poco::RegularExpression regex(regex_string);
  std::vector<std::string> results;
  int limit = stream.ConsumeIntegral<int>();
  int result = regex.split(input_string, results, limit);

  return result;
}