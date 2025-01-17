#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "vsb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a VSB instance
  struct vsb s;
  VSB_init(&s, NULL, 0);

  // Extract prefix string
  std::string pfx = stream.ConsumeRandomLengthString();
  
  // Extract value string
  std::string v = stream.ConsumeRemainingBytesAsString();

  // Quote the string
  VSB_quote_pfx(&s, pfx.c_str(), v.c_str(), v.size(), stream.ConsumeIntegral<int>());

  // Clean up
  VSB_clear(&s);

  return 0;
}