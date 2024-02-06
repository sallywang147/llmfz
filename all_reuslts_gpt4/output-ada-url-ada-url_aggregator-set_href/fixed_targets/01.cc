#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "ada/url_aggregator.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ada::url_aggregator aggregator;
  
  std::string str = stream.ConsumeRandomLengthString();
  char *input = const_cast<char*>(str.c_str());

  ada::url_aggregator::set_href(&aggregator, input, size);

  return 0;
}