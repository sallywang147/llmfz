#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string buffer = provider.ConsumeRemainingBytesAsString();
  
  GumboInternalOutput* output = gumbo_parse(const_cast<char*>(buffer.c_str()));
  if (output != nullptr) {
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }
  
  return 0;
}