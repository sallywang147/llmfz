#include <fuzzer/FuzzedDataProvider.h>
#include "astc_codec_internals.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int xdim = stream.ConsumeIntegral<int>();
  int ydim = stream.ConsumeIntegral<int>();
  int zdim = stream.ConsumeIntegral<int>();

  bool ret = is_legal_3d_block_size(xdim, ydim, zdim);

  return 0;
}