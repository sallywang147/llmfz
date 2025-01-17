 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "zstd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_compressed_size = stream.ConsumeIntegral<size_t>();
  const size_t max_input_size = stream.ConsumeIntegral<size_t>();
  ZSTD_CCtx* cctx = ZSTD_createCCtx();
  if (cctx == nullptr) {
    return 0;
  }

  std::vector<uint8_t> input_buffer(stream.ConsumeRemainingBytes());
  if (input_buffer.size() > max_input_size) {
    input_buffer.resize(max_input_size);
  }

  std::vector<uint8_t> output_buffer(max_compressed_size);

  size_t compressed_size = ZSTD_compress2(cctx, output_buffer.data(),
                                          output_buffer.size(), input_buffer.data(),
                                          input_buffer.size());
  ZSTD_freeCCtx(cctx);
  return 0;
}