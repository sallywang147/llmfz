#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  std::vector<uint8_t> input_buffer = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, size));
  std::vector<uint8_t> output_buffer(ZSTD_compressBound(input_buffer.size()));

  const size_t compressed_size = ZSTD_compress2(cctx, output_buffer.data(), output_buffer.size(),
                                                input_buffer.data(), input_buffer.size());
  if (ZSTD_isError(compressed_size)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}