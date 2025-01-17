#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

extern "C" {
#include "Poco/RegularExpression.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRemainingBytesAsString();
  std::string regex = provider.ConsumeRemainingBytesAsString();

  Poco::RegularExpression re(regex);
  std::vector<std::string> matches;
  re.split(input, matches);

  return 0;
}