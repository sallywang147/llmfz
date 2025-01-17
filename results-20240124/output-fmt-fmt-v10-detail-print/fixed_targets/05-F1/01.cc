#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t max_size = 1024;
  char text[max_size];
  const size_t text_size = stream.ConsumeIntegralInRange<size_t>(0, max_size);
  stream.ConsumeBytes(text, text_size);

  fmt::print(stdout, text);

  return 0;
}