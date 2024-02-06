#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "hb.h"
#include "hb-shape.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const double x = stream.ConsumeFloatingPoint<double>();
  hb_shape_justify::anon* this_ = nullptr;
  double (hb_shape_justify::$_3::*op)(anon * this, double x) const = &hb_shape_justify::$_3::operator();
  (this_->*op)(this_, x);
  return 0;
}