#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hb-shape-justify.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // The function solve_itp requires a pointer to an anonymous struct. Since we don't know the structure of this struct, we can't generate a meaningful instance. Instead, we'll pass a nullptr.
  anon *f = nullptr;

  // Generate the remaining parameters using the FuzzedDataProvider.
  double a = stream.ConsumeFloatingPoint<double>();
  double b = stream.ConsumeFloatingPoint<double>();
  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();

  // These are output parameters. We'll initialize them to zero.
  double ya = 0.0;
  double yb = 0.0;
  double y = 0.0;

  // Call the function with the generated parameters.
  double result = solve_itp<hb_shape_justify::$_3>(f, a, b, epsilon, min_y, max_y, &ya, &yb, &y);

  return 0;
}