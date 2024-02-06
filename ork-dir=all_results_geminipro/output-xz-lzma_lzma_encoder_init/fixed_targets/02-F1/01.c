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
    lzma_init();
    initialized = true;
  }

  lzma_allocator allocator = LZMA_ALLOCATOR_INIT;
  lzma_next_coder next_coder;
  lzma_filter_info_s filters[2] = {
    {
      .id = LZMA_FILTER_LZMA2,
      .init = nullptr,
      .options = nullptr,
    },
    {
      .id = LZMA_FILTER_LZMA2,
      .init = nullptr,
      .options = nullptr,
    },
  };

  FuzzedDataProvider provider(data, size);
  size_t filter_count = provider.ConsumeIntegralInRange<size_t>(0, 2);
  for (size_t i = 0; i < filter_count; i++) {
    filters[i].id = provider.ConsumeIntegral<uint64_t>();
    filters[i].options = provider.ConsumeBytes<void>(
        provider.ConsumeIntegralInRange<size_t>(0, 1024));
  }

  int ret = lzma_lzma_encoder_init(&next_coder, &allocator, filters);
  if (ret != LZMA_OK) {
    return 0;
  }

  lzma_filter_info_s filter_info;
  ret = lzma_next_coder_get_filter_info(&next_coder, &filter_info);
  if (ret != LZMA_OK) {
    return 0;
  }

  std::vector<uint8_t> output_buffer(filter_info.output_buffer_size);
  size_t output_written = 0;
  // Initially, start by feeding the decoder more data.
  int decode_ret = LZMA_OK;
  while ((decode_ret != LZMA_STREAM_END)) {
    if (decode_ret == LZMA_OK) {
      if (provider.remaining_bytes() == 0) {
        break;
      }
      const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
          0,
          provider.remaining_bytes());
      auto next_input = provider.ConsumeBytes<uint8_t>(next_size);
      decode_ret = lzma_next_coder_encode(&next_coder, next_input.data(),
                                         next_input.size(), output_buffer.data(),
                                         &output_written);
    } else if (decode_ret != LZMA_STREAM_END) {
      decode_ret = lzma_next_coder_encode(&next_coder, nullptr, 0,
                                         output_buffer.data(), &output_written);
    } else {
      // Unhandled lzma_next_coder_encode return value.
      abort();
    }
  }

  lzma_next_coder_end(&next_coder, &allocator);

  return 0;
}
```

The issue is that the `lzma_filter_info_s` struct is defined with the `LZMA_FILTER_LZMA2` filter ID, but the `lzma_lzma_encoder_init()` function is called with the `LZMA_FILTER_LZMA1` filter ID. To fix this, the `LZMA_FILTER_LZMA2` filter ID should be used in the `lzma_lzma_encoder_init()` function.