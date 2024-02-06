#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hb-shape-justify.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  anon f;
  double a = stream.ConsumeFloatingPoint<double>();
  double b = stream.ConsumeFloatingPoint<double>();
  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();
  double ya = stream.ConsumeFloatingPoint<double>();
  double yb = stream.ConsumeFloatingPoint<double>();
  double y = stream.ConsumeFloatingPoint<double>();

  solve_itp<hb_shape_justify::$_3>(&f, a, b, epsilon, min_y, max_y, &ya, &yb, &y);

  return 0;
}