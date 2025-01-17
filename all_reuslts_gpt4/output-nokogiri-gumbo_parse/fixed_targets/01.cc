#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gumbo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string buffer = stream.ConsumeRemainingBytesAsString();

  GumboInternalOutput* output = gumbo_parse((char*)buffer.c_str());

  if (output) {
    gumbo_destroy_output(&kGumboDefaultOptions, output);
  }

  return 0;
}