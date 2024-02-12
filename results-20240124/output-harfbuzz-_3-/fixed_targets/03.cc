#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <iostream>

struct anon {
  double a;
  double b;
};

double solve_itp(anon * f, double a, double b, double epsilon, double min_y, double max_y, double * ya, double * yb, double * y) {
  double y_a = 0;
  double y_b = 0;
  double y_c = 0;
  double delta = 0;

  if (f->a == 0) {
    return 0;
  }

  y_a = f->b / f->a;
  y_b = y_a;
  y_c = y_a;

  while (true) {
    delta = (y_b - y_a) / 2;
    y_c = y_b - delta;

    if (y_c < min_y || y_c > max_y) {
      y_b = y_c;
    } else {
      break;
    }
  }

  *ya = y_a;
  *yb = y_b;
  *y = y_c;

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  anon f;
  f.a = stream.ConsumeFloatingPoint<double>();
  f.b = stream.ConsumeFloatingPoint<double>();

  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();

  double ya = 0;
  double yb = 0;
  double y = 0;

  solve_itp(&f, a, b, epsilon, min_y, max_y, &ya, &yb, &y); // Call the function

  return 0;
}