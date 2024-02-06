#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hb.h"

struct anon {};

class hb_shape_justify {
 public:
  class $_3 {
   public:
    double operator()(anon* this_, double x) const {
      // Implementation is not provided here.
      return 0.0;
    }
  };
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  anon this_;
  double x = stream.ConsumeFloatingPoint<double>();

  hb_shape_justify::$_3 justify_operator;
  double result = justify_operator(&this_, x);

  return 0;
}