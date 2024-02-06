#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate valid input values
  int xdim = stream.ConsumeIntegralInRange<int>(1, 16);
  int ydim = stream.ConsumeIntegralInRange<int>(1, 16);

  // Call the function under test
  bool result = is_legal_2d_block_size(xdim, ydim);

  // Use the result
  (void)result;

  return 0;
}