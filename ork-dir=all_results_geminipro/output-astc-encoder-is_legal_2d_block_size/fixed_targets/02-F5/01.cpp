#include <fuzzer/FuzzedDataProvider.h>
#include <cmath>

extern "C" {
#include <stdbool.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  int xdim = fdp.ConsumeIntegral<int>();
  int ydim = fdp.ConsumeIntegral<int>();
  bool result = is_legal_2d_block_size(xdim, ydim);
  return 0;
}

bool is_legal_2d_block_size(int xdim, int ydim) {
  // Check if the dimensions are positive.
  if (xdim <= 0 || ydim <= 0) {
    return false;
  }

  // Check if the dimensions are within the allowed range.
  if (xdim > 1024 || ydim > 1024) {
    return false;
  }

  // Check if the dimensions are powers of two.
  if ((xdim & (xdim - 1)) != 0 || (ydim & (ydim - 1)) != 0) {
    return false;
  }

  // The dimensions are legal.
  return true;
}