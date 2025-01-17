#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "zstd.h"

extern "C" {
#include "zstd.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> input_buffer(stream.ConsumeIntegralInRange<size_t>(
      0, std::min(size, static_cast<size_t>(ZSTD_BLOCKSIZE_MAX))));
  stream.ConsumeBytes(input_buffer.data(), input_buffer.size());
  ZSTD_inBuffer in_buffer = {input_buffer.data(), input_buffer.size(), 0};
  size_t ret = ZSTD_endStream(cctx, &in_buffer);
  if (ZSTD_isError(ret)) {
    fprintf(stderr, "ZSTD_endStream returned error: %s\n", ZSTD_getErrorName(ret));
  }
  ZSTD_freeCCtx(cctx);
  return 0;
}