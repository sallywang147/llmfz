#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "fmt/core.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t count = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  const char* ptr = reinterpret_cast<const char*>(stream.ConsumeBytes<uint8_t>(count).data());
  fwrite(ptr, 1, count, stdout);
  return 0;
}