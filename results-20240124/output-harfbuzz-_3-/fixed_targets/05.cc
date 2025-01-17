#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "hb-fuzzer.hh"

extern "C" {
#include "hb.h"
}

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
  double solve_itp_result = solve_itp<hb_shape_justify::$_3>(&f, a, b, epsilon, min_y, max_y, &ya, &yb, &y);
  return 0;
}

extern "C" double solve_itp(anon * f, double a, double b, double epsilon, double min_y, double max_y, double * ya, double * yb, double * y) {
  return solve_itp<hb_shape_justify::$_3>(f, a, b, epsilon, min_y, max_y, ya, yb, y);
}