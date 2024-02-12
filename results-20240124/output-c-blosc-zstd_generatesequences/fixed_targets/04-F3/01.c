#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "zstd.h"

extern "C" {
#include "zstd_errors.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_input_size = stream.ConsumeIntegral<size_t>();
  const size_t max_output_size = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> input_buffer(max_input_size);
  stream.ConsumeBytes(input_buffer.data(), max_input_size);

  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  size_t const ret = ZSTD_generateSequences(cctx, nullptr, 0, reinterpret_cast<char*>(input_buffer.data()), max_input_size);
  if (ZSTD_isError(ret)) {
    ZSTD_freeCCtx(cctx);
    return 0;
  }

  ZSTD_freeCCtx(cctx);
  return 0;
}