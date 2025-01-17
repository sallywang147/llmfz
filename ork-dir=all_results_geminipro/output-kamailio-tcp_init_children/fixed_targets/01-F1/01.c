#include <fuzzer/FuzzedDataProvider.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int woneinit = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  tcp_init_children(&woneinit);

  return 0;
}