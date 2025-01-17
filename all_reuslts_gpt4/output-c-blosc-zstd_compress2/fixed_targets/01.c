#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  // Prepare the input and output buffers.
  size_t input_size = stream.remaining_bytes() / 2;
  std::string input = stream.ConsumeBytesAsString(input_size);
  size_t output_size = ZSTD_compressBound(input_size);
  std::vector<char> output(output_size);

  // Compress the input into the output buffer.
  size_t ret = ZSTD_compress2(cctx, output.data(), output_size, input.data(), input_size);

  ZSTD_freeCCtx(cctx);

  return 0;
}