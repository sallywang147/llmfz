#include <fuzzer/FuzzedDataProvider.h>
#include <cassert>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int xdim = stream.ConsumeIntegralInRange<int>(0, 1024);
  int ydim = stream.ConsumeIntegralInRange<int>(0, 1024);
  int zdim = stream.ConsumeIntegralInRange<int>(0, 1024);

  // Call the function under test
  bool result = is_legal_3d_block_size(xdim, ydim, zdim);

  // Check the result
  assert(result == (xdim > 0 && ydim > 0 && zdim > 0));

  return 0;
}