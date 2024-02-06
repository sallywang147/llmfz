#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "wp_log2s.h"
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  int value = fuzzed_data.ConsumeIntegral<int>();
  wp_log2s(value);
  return 0;
}