#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "hb.h"

struct anon {};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for the function
  anon obj;
  double x = stream.ConsumeFloatingPoint<double>();

  // Create an instance of the hb_shape_justify::$_3 class
  hb_shape_justify::$_3 justify;

  // Call the function with the initialized parameters
  double result = justify.operator()(&obj, x);

  return 0;
}