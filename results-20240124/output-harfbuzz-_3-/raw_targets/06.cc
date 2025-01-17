 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include <cmath>
#include <vector>

#include "hb-fuzzer.hh"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  double a = stream.ConsumeFloatingPoint<double>();
  double b = stream.ConsumeFloatingPoint<double>();
  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();
  double ya = stream.ConsumeFloatingPoint<double>();
  double yb = stream.ConsumeFloatingPoint<double>();
  double y = stream.ConsumeFloatingPoint<double>();

  double result = solve_itp<hb_shape_justify::$_3>(nullptr, a, b, epsilon, min_y, max_y, &ya, &yb, &y);
  (void) result;

  return 0;
}