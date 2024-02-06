#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  int xdim = fdp.ConsumeIntegral<int>();
  int ydim = fdp.ConsumeIntegral<int>();
  bool result = is_legal_2d_block_size(xdim, ydim);
  return 0;
}