#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "lzma.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct lzma_next_coder_s next;
  struct lzma_allocator allocator;
  struct lzma_filter_info_s filters[2] = {
      {LZMA_FILTER_LZMA2, nullptr},
      {LZMA_VLI_UNKNOWN, nullptr},
  };

  // Initialize allocator.
  allocator.alloc = nullptr;
  allocator.free = nullptr;
  allocator.opaque = nullptr;

  // Initialize next coder.
  lzma_next_coder_init(&next, &allocator);

  // Initialize filters.
  lzma_filter_info_init(&filters[0]);
  lzma_filter_info_init(&filters[1]);

  // Initialize lzma_lzma_encoder_init.
  int ret = lzma_lzma_encoder_init(&next, &allocator, filters);
  if (ret != LZMA_OK) {
    fprintf(stderr, "lzma_lzma_encoder_init() failed (%d)\n", ret);
    abort();
  }

  // Feed data to the encoder.
  std::vector<uint8_t> output_buffer(1024);
  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    size_t next_size = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<uint8_t>(next_size);
    ret = lzma_next_coder_encode(&next, &allocator, next_input.data(), next_input.size(), output_buffer.data(), &next_size);
    if (ret != LZMA_OK) {
      fprintf(stderr, "lzma_next_coder_encode() failed (%d)\n", ret);
      abort();
    }
  }

  // Flush the encoder.
  ret = lzma_next_coder_encode(&next, &allocator, nullptr, 0, output_buffer.data(), &next_size);
  if (ret != LZMA_OK) {
    fprintf(stderr, "lzma_next_coder_encode() failed (%d)\n", ret);
    abort();
  }

  // Cleanup.
  lzma_next_coder_end(&next, &allocator);
  lzma_filter_info_end(&filters[0]);
  lzma_filter_info_end(&filters[1]);

  return 0;
}