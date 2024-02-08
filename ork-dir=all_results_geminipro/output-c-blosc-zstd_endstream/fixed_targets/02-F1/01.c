#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" {
#include "zstd.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ZSTD_initCStream();
    initialized = true;
  }
  int ret;
  ZSTD_CCtx* handle = ZSTD_createCCtx();
  if (handle == nullptr) {
    return 0;
  }

  ZSTD_inBuffer input = {data, size, 0};
  ZSTD_outBuffer output = {nullptr, 0, 0};

  size_t output_written = 0;
  // Initially, start by feeding the decoder more data.
  int decode_ret = ZSTD_compressStream(handle, &output, &input);
  FuzzedDataProvider provider(data, size);
  while ((decode_ret != ZSTD_closed)) {
    if (decode_ret == ZSTD_needDict) {
      break;
    } else if (decode_ret == ZSTD_partial_out) {
      if (provider.remaining_bytes() == 0) {
        break;
      }
      const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
          0,
          provider.remaining_bytes());
      auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
      input.src = next_input.data();
      input.size = next_input.size();
      input.pos = 0;
      decode_ret = ZSTD_compressStream(handle, &output, &input);
    } else if (decode_ret != ZSTD_needDst) {
      // Unhandled mpg123_decode return value.
      abort();
    }
  }

  ZSTD_endStream(handle, &input);
  ZSTD_freeCCtx(handle);

  return 0;
}