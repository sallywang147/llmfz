#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lzma.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    lzma_lzma_encoder_init();
    initialized = true;
  }

  struct lzma_lz_encoder lz;
  lzma_lz_encoder_init(&lz);

  struct lzma_allocator allocator;
  allocator.alloc = nullptr;
  allocator.free = nullptr;

  struct lzma_lz_options lz_options;
  lzma_lz_options_init(&lz_options);

  FuzzedDataProvider provider(data, size);
  size_t id = provider.ConsumeIntegralInRange<size_t>(0, 1000);
  std::string options = provider.ConsumeRemainingBytesAsString();

  int ret = lzma_encoder_init(&lz, &allocator, id, options.c_str(),
                             &lz_options);
  if (ret != LZMA_OK) {
    return 0;
  }

  lzma_lz_encoder_end(&lz);

  return 0;
}