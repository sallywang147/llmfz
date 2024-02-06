#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "anon.h"
#include "hb-shape-justify.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  anon *f = new anon();
  double a = stream.ConsumeFloatingPoint<double>();
  double b = stream.ConsumeFloatingPoint<double>();
  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();
  double *ya = new double();
  double *yb = new double();
  double *y = new double();

  solve_itp<hb_shape_justify::hb_$_3>(f, a, b, epsilon, min_y, max_y, ya, yb, y);

  delete f;
  delete ya;
  delete yb;
  delete y;
  return 0;
}
```

The corrected code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "anon.h"
#include "hb-shape-justify.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  anon *f = new anon();
  double a = stream.ConsumeFloatingPoint<double>();
  double b = stream.ConsumeFloatingPoint<double>();
  double epsilon = stream.ConsumeFloatingPoint<double>();
  double min_y = stream.ConsumeFloatingPoint<double>();
  double max_y = stream.ConsumeFloatingPoint<double>();
  double *ya = new double();
  double *yb = new double();
  double *y = new double();

  solve_itp<hb_shape_justify::hb_$_3>(f, a, b, epsilon, min_y, max_y, ya, yb, y);

  delete f;
  delete ya;
  delete yb;
  delete y;
  return 0;
}