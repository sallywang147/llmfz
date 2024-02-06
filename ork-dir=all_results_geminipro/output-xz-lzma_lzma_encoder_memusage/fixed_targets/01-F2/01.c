#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "lzma.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }
  FuzzedDataProvider provider(data, size);
  size_t options_size = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<char> options(options_size);
  provider.ConsumeBytes(options.data(), options_size);
  lzma_lzma_encoder_memusage(options.data());
  return 0;
}