#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "Poco/RegularExpression.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRemainingBytesAsString();
  std::string pattern = provider.ConsumeRemainingBytesAsString();
  std::string replacement = provider.ConsumeRemainingBytesAsString();
  Poco::RegularExpression regex(pattern);
  size_t offset = provider.ConsumeIntegralInRange<size_t>(0, input.size());
  regex.substOne(&input, offset, replacement, 0);
  return 0;
}