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
  size_t max_mem = provider.ConsumeIntegralInRange<size_t>(0, 1 << 20);

  std::vector<char> options(max_mem);
  size_t options_size = provider.ConsumeRemainingBytes(options.data(), max_mem);

  size_t memusage = lzma_lzma2_encoder_memusage(options.data(), options_size);
  if (memusage == 0) {
    fprintf(stderr, "lzma_lzma2_encoder_memusage() failed\n");
    abort();
  }

  return memusage;
}