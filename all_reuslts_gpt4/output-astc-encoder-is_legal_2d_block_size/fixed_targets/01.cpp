#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int xdim = stream.ConsumeIntegral<int>();
  int ydim = stream.ConsumeIntegral<int>();

  is_legal_2d_block_size(xdim, ydim);

  return 0;
}