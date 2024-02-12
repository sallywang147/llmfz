 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t chunk_size = stream.ConsumeIntegralInRange<size_t>(
      0, std::min(size, ZSTD_BLOCKSIZE_MAX));
  std::vector<uint8_t> input_buffer(chunk_size);
  stream.ConsumeBytes<uint8_t>(input_buffer.data(), chunk_size);

  ZSTD_CCtx* const cctx = ZSTD_createCCtx();
  ZSTD_inBuffer input = {input_buffer.data(), chunk_size, 0};
  ZSTD_outBuffer output = {nullptr, 0, 0};

  size_t ret;
  while ((ret = ZSTD_compressStream(cctx, &output, &input)) == 0) {
    output.dst = nullptr;
    output.size = ZSTD_compressBound(input.size);
    output.pos = 0;
  }

  ZSTD_freeCCtx(cctx);

  return 0;
}