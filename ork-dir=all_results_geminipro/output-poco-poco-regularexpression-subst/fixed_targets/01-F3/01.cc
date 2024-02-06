#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Poco/RegularExpression.h"

extern "C" {
#include "Poco/RegularExpression.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  std::string pattern = stream.ConsumeRemainingBytesAsString();
  std::string replacement = stream.ConsumeRemainingBytesAsString();

  Poco::RegularExpression regex(pattern);
  int result = regex.subst(&input_string, 0, &replacement, 0);

  return 0;
}