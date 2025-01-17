#include <zstd.h>
#include <iostream>

extern "C" {
#include <stdio.h>
}

int main() {
  // Create a compression context
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (!cctx) {
    std::cerr << "Error creating compression context" << std::endl;
    return 1;
  }

  // Set the compression level
  ZSTD_CCtx_setParameter(cctx, ZSTD_c_compressionLevel, 3);

  // Compress the data
  size_t compressedSize = ZSTD_compressStream(cctx, stdout, stdin, ZSTD_e_end);
  if (ZSTD_isError(compressedSize)) {
    std::cerr << "Error compressing data: " << ZSTD_getErrorName(compressedSize) << std::endl;
    ZSTD_freeCCtx(cctx);
    return 1;
  }

  // Flush the stream
  ZSTD_flushStream(cctx);

  // Free the compression context
  ZSTD_freeCCtx(cctx);

  return 0;
}