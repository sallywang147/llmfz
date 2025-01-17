#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <string>

#include "const.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const double input = stream.ConsumeFloatingPoint<double>();
  // Call the function `const_` with the input
  const double output = const_(input);
  (void)output;
  return 0;
}

// Define the missing function
double const_(double input) {
  return input + 1.0;
}