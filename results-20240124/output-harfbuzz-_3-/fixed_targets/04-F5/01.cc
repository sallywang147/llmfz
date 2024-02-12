#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>

struct anon {
  double a;
  double b;
};

extern "C" {
#include "hb-shape.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  anon* f = new anon();
  f->a = stream.ConsumeFloatingPoint<double>();
  f->b = stream.ConsumeFloatingPoint<double>();

  double a = stream.ConsumeFloatingPoint<double>();
  double b = stream.ConsumeFloatingPoint<double>();
  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();

  double ya = 0;
  double yb = 0;
  double y = 0;

  // Call the function
  solve_itp<hb_shape_justify::$_3>(f, a, b, epsilon, min_y, max_y, &ya, &yb, &y);

  delete f;

  return 0;
}