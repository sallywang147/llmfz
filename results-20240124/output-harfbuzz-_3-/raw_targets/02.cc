 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "hb.h"
#include "hb-fuzzer.hh"

struct anon
{
  double a;
  double b;
  double c;
  double d;
  double e;
  double f;
  double g;
  double h;
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  anon f;
  f.a = stream.ConsumeFloatingPoint<double>();
  f.b = stream.ConsumeFloatingPoint<double>();
  f.c = stream.ConsumeFloatingPoint<double>();
  f.d = stream.ConsumeFloatingPoint<double>();
  f.e = stream.ConsumeFloatingPoint<double>();
  f.f = stream.ConsumeFloatingPoint<double>();
  f.g = stream.ConsumeFloatingPoint<double>();
  f.h = stream.ConsumeFloatingPoint<double>();
  double a = stream.ConsumeFloatingPoint<double>();
  double b = stream.ConsumeFloatingPoint<double>();
  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();
  double ya = 0;
  double yb = 0;
  double y = 0;
  double solve_itp_result = solve_itp<hb_shape_justify::$_3>(&f, a, b, epsilon, min_y, max_y, &ya, &yb, &y);
  return 0;
}