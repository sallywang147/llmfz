#include "astcenc_internal.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int xdim = stream.ConsumeIntegralInRange<int>(1, 16);
  int ydim = stream.ConsumeIntegralInRange<int>(1, 16);
  int zdim = stream.ConsumeIntegralInRange<int>(1, 16);

  bool result = is_legal_3d_block_size(xdim, ydim, zdim);

  return 0;
}