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
  static bool initialized = false;
  if (!initialized) {
    lzma_init();
    initialized = true;
  }
  int ret;
  lzma_stream strm = LZMA_STREAM_INIT;
  ret = lzma_easy_encoder(&strm, 9, LZMA_CHECK_CRC64);
  if (ret != LZMA_OK) {
    fprintf(stderr, "lzma_easy_encoder() failed (%d)\n", ret);
    abort();
  }

  std::vector<uint8_t> output_buffer(1 << 20);
  size_t output_written = 0;

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        provider.remaining_bytes());
    auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
    ret = lzma_encode(&strm, next_input.data(), next_input.size(),
                      output_buffer.data(), &output_written,
                      output_buffer.size());
    if (ret != LZMA_OK) {
      fprintf(stderr, "lzma_encode() failed (%d)\n", ret);
      abort();
    }
  }

  lzma_end(&strm);

  return 0;
}