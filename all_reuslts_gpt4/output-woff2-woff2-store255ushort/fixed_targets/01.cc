#include <fuzzer/FuzzedDataProvider.h>
#include <woff2/variable_length.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  // Extract the integer value
  int val = stream.ConsumeIntegral<int>();
  
  // Initialize the offset to 0
  size_t offset = 0;
  
  // Create a buffer to store the result
  char dst[5];  // Maximum size needed for Store255UShort

  // Call the function under test
  woff2::Store255UShort(val, &offset, dst);

  return 0;
}