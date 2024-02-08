#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int xdim = stream.ConsumeIntegral<int>();
  int ydim = stream.ConsumeIntegral<int>();
  int zdim = stream.ConsumeIntegral<int>();

  is_legal_3d_block_size(xdim, ydim, zdim);

  return 0;
}