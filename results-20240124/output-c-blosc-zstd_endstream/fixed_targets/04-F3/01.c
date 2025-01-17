#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "zstd.h"

extern "C" {
#include "zstd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }
  ZSTD_inBuffer input = {nullptr, 0, 0};
  std::vector<unsigned char> compressed_buffer;
  while (stream.remaining_bytes()) {
    size_t input_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    input.src = stream.ConsumeBytes<unsigned char>(input_size).data();
    input.size = input_size;
    input.pos = 0;
    ZSTD_compressStream2(cctx, compressed_buffer.data(), compressed_buffer.size(), &input);
  }
  ZSTD_endStream(cctx, nullptr);
  ZSTD_freeCCtx(cctx);
  return 0;
}