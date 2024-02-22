#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "astc_codec_internals.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int xdim = stream.ConsumeIntegral<int>();
  const int ydim = stream.ConsumeIntegral<int>();
  const int zdim = stream.ConsumeIntegral<int>();

  is_legal_3d_block_size(xdim, ydim, zdim);
  return 0;
}