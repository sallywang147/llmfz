#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lzma.h"

extern "C" {
#include "lzma.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t options_size = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<char> options(options_size);
  provider.ConsumeBytes(options.data(), options_size);
  size_t memusage = lzma_lzma2_encoder_memusage(options.data(), options_size); // Added the second argument, options_size
  return memusage;
}