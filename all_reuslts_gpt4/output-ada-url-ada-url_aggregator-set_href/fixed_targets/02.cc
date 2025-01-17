#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "ada/url_aggregator.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ada::url_aggregator aggregator;
  std::string input = stream.ConsumeRemainingBytesAsString();
  aggregator.set_href(&aggregator, const_cast<char*>(input.c_str()), input.size());

  return 0;
}