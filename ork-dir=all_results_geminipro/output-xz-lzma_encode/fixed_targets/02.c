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

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    lzma_init();
    initialized = true;
  }

  lzma_mf mf;
  if (lzma_mf_init(&mf) != LZMA_OK) {
    return 0;
  }

  std::vector<uint8_t> output_buffer(size * 2);
  size_t output_written = 0;

  lzma_filter filters[2] = {{
                                .id = LZMA_FILTER_LZMA2,
                                .options = &mf,
                            },
                            {
                                .id = LZMA_VLI_UNKNOWN,
                            }};

  lzma_stream strm = LZMA_STREAM_INIT;
  if (lzma_stream_encoder(&strm, filters, LZMA_CHECK_CRC64) != LZMA_OK) {
    lzma_mf_free(&mf);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  while (provider.remaining_bytes() > 0) {
    auto next_input = provider.ConsumeBytes<uint8_t>(provider.remaining_bytes());
    lzma_ret ret = lzma_code(&strm, next_input.data(), next_input.size(),
                               output_buffer.data(), &output_written,
                               output_buffer.size());
    if (ret != LZMA_OK && ret != LZMA_STREAM_END) {
      lzma_mf_free(&mf);
      lzma_end(&strm);
      return 0;
    }
  }

  lzma_mf_free(&mf);
  lzma_end(&strm);

  return 0;
}
```
The only change is in the line:
```c++
lzma_ret ret = lzma_code(&strm, next_input.data(), next_input.size(),
```
The original code has a typo in the `lzma_code` function call. It should be `lzma_code` instead of `lzma_encode`. This typo causes the build error.