#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "hb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const double x = stream.ConsumeFloatingPoint<double>();
  const hb_shape_justify::anon* this_ = nullptr;
  double hb_shape_justify::$_3::operator(anon * this, double x) const {
    return 0;
  }
  hb_shape_justify::$_3::operator(this_, x);
  return 0;
}