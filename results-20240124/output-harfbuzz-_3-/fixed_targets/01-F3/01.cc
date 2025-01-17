#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <cstdio>

extern "C" {
#include "solve_itp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  anon f;
  double a = provider.ConsumeFloatingPoint<double>();
  double b = provider.ConsumeFloatingPoint<double>();
  double epsilon = provider.ConsumeFloatingPoint<double>();
  double min_y = provider.ConsumeFloatingPoint<double>();
  double max_y = provider.ConsumeFloatingPoint<double>();
  double ya;
  double yb;
  double y;
  double result = solve_itp<hb_shape_justify::$_3>(&f, a, b, epsilon, min_y, max_y, &ya, &yb, &y);
  // Call the target function
  solve_itp<hb_shape_justify::$_3>(&f, a, b, epsilon, min_y, max_y, &ya, &yb, &y);
  printf("result: %f\n", result);
  return 0;
}