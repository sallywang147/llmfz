#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "lz4hc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a compression context.
  LZ4_streamHC_t ctx;
  LZ4_resetStreamHC(&ctx, 0);

  // Create a buffer for the compressed data.
  size_t compressed_size = LZ4_compressBound(size);
  std::vector<char> compressed_buffer(compressed_size);

  // Compress the data.
  int result = LZ4_compressHC_continue(&ctx, reinterpret_cast<const char*>(data),
                                      compressed_buffer.data(), size);
  if (result < 0) {
    return 0;
  }

  // Decompress the data.
  std::vector<char> decompressed_buffer(size);
  result = LZ4_decompress_safe(compressed_buffer.data(), decompressed_buffer.data(),
                              result, size);
  if (result < 0) {
    return 0;
  }

  // Compare the original and decompressed data.
  if (memcmp(data, decompressed_buffer.data(), size) != 0) {
    return 0;
  }

  return 0;
}