#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the compression context.
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  // Create an input buffer.
  ZSTD_inBuffer input_buffer = {data, size, 0};

  // Create an output buffer.
  std::vector<uint8_t> output_buffer(ZSTD_compressBound(size));
  ZSTD_outBuffer output_buffer_struct = {output_buffer.data(), output_buffer.size(), 0, 0};

  // Compress the input data.
  size_t compressed_size = ZSTD_compressStream(cctx, &output_buffer_struct, &input_buffer);
  if (ZSTD_isError(compressed_size)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  // Flush the remaining data in the compression context.
  size_t remaining_size = ZSTD_flushStream(cctx, &output_buffer_struct);
  if (ZSTD_isError(remaining_size)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  // Free the compression context.
  ZSTD_freeCCtx(cctx);

  return 0;
}