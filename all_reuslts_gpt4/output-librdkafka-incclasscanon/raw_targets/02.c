#include <fuzzer/FuzzedDataProvider.h>

#include "regexp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Reclass struct
  struct Reclass cc;
  cc.end = stream.ConsumeIntegral<uint8_t>();
  cc.span = stream.ConsumeIntegral<uint8_t>();
  cc.start = stream.ConsumeIntegral<uint8_t>();

  // Consume an integer for the second argument
  int c = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  incclasscanon(&cc, c);

  return 0;
}